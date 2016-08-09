
#include "tcphandler.h"
#include <assert.h>
static int readtimes = 0;
//������¼�
void TcpHandler::dealReadEvent()
{
	cout << "m_pLastNode addr is:  " << m_pLastNode <<endl;
	if(m_pLastNode)
	{
		cout << "m_pLastNode msglen is:  "<< m_pLastNode->m_nMsgLen <<endl;
		cout << "m_pLastNode m_nOffSet is: " << m_pLastNode->m_nOffSet <<endl;
	}
	else
	{
		cout << "m_pLastNode addr is null!!!" <<endl;
	}
	

	evbuffer * inputBuf = bufferevent_get_input(m_pBufferevent);
	size_t inputLen = evbuffer_get_length(inputBuf);
	cout <<"total len is : "<<  inputLen <<endl;
	while(inputLen > 0)
	{
		//tcphandler��һ�ν�����Ϣ���߸�node��������Ϣ����Ҫ�����µ�node������Ϣ
		if(!m_pLastNode || m_pLastNode->m_nMsgLen <= m_pLastNode->m_nOffSet)
		{
			//�ж���Ϣ�����Ƿ������ͷ��С������������
			if(inputLen  < PACKETHEADLEN)
			{
				break;
			}

			char data[PACKETHEADLEN]  = {0};
			bufferevent_read(m_pBufferevent, data, PACKETHEADLEN);
			struct PacketHead  packetHead;

			memcpy(&packetHead, data, PACKETHEADLEN);

			cout << "packetId is : " <<packetHead.packetID << endl;

			cout << "packetLen is :  " << packetHead.packetLen << endl;

			insertNode(packetHead.packetID, packetHead.packetLen);

			inputLen -= PACKETHEADLEN;
			cout << "after remove head the length is : " << inputLen <<endl;
		}

		//���ǿ���ȥ��ͷ��ʣ���Ϊ0
		if(inputLen <= 0)
		{
			break;
		}
		//��ȡȥ����ͷ��ʣ����Ϣ
		tcpRead(inputLen);
	}

	
}

void TcpHandler::dealWriteEvent(std::string strSend)
{
	bufferevent_write(m_pBufferevent, strSend.c_str(), strSend.size());
}


list<MsgNode *> * TcpHandler::getListMsgs(void)
{
	return &m_listMsgs;
}

const UInt64 &TcpHandler::getConnId(void)
{
	return m_nConnId;
}

void TcpHandler::tcpRead(UInt32 &inputLen)
{
	//node�ڵ��е����ݻ��ж���û����
	assert(m_pLastNode->m_nMsgLen >= m_pLastNode->m_nOffSet);
	UInt32 remainLen = m_pLastNode->m_nMsgLen - m_pLastNode->m_nOffSet;
	cout << "remainLen is: " <<remainLen << endl;
	
	UInt32 readLen = bufferevent_read(m_pBufferevent, m_pLastNode->m_pMsg + m_pLastNode->m_nOffSet, remainLen);
	cout << "tcp read len is : " << readLen <<endl;

	//ͳ��bufferevent ��inputbuffer��ʣ��ĳ���
	inputLen -= readLen;
	//����ƫ�Ʊ��
	m_pLastNode->m_nOffSet += readLen;
	cout << "after read  offset is :  " <<m_pLastNode->m_nOffSet <<endl;

	//�ж϶���
	if(m_pLastNode->m_nOffSet >= m_pLastNode->m_nMsgLen)
	{
		m_pLastNode->m_pMsg[m_pLastNode->m_nMsgLen ] = '\0'; 
		cout << "receive msg is : " << m_pLastNode->m_pMsg << endl;
		cout <<"read times is :  " << ++readtimes<< endl;

		m_pLastNode = NULL;
		
	}

}

void TcpHandler::tcpSend(UInt32 msgId, UInt32 msgLen, char * msg)
{

}

bool MsgNode::isReceived()
{
	if(m_nOffSet >= m_nMsgLen)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TcpHandler::insertNode(UInt32 msgId, UInt32 msgLen)
{
	readtimes++;
	cout << "insert node : "<< readtimes << endl;
	cout << "msgId is: " << msgId << endl;
	cout << "msgLen is: " <<msgLen <<endl;

	MsgNode * msgNode = new MsgNode(msgId, msgLen);
	if(!msgNode)
	{
		assert(false);
		return false;
	}

	m_listMsgs.push_back(msgNode);

	m_pLastNode = msgNode;
	cout <<"new m_pLastNode addr is:  " <<m_pLastNode << endl;
	

	return true;
}