
#include "stdafx.h"
#include "tcphandler.h"
//������¼�
void TcpHandler::dealReadEvent()
{
	evbuffer * inputBuf = bufferevent_get_input(m_pBufferevent);
	size_t inputLen = evbuffer_get_length(inputBuf);

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

void TcpHandler::tcpRead(UInt32 &inputLen)
{
	//node�ڵ��е����ݻ��ж���û����
	UInt32 remainLen = m_pLastNode->m_nMsgLen - m_pLastNode->m_nOffSet;

	UInt32 readLen = bufferevent_read(m_pBufferevent, m_pLastNode->m_pMsg + m_pLastNode->m_nOffSet, remainLen);
	//ͳ��bufferevent ��inputbuffer��ʣ��ĳ���
	inputLen -= readLen;
	//����ƫ�Ʊ��
	m_pLastNode->m_nOffSet += readLen;
	//�ж϶���
	if(m_pLastNode->m_nOffSet >= m_pLastNode->m_nMsgLen)
	{
		m_pLastNode->m_pMsg[m_pLastNode->m_nMsgLen + 1] = '\0'; 
		cout << "receive msg is : " << m_pLastNode->m_pMsg << endl;
	}

}


bool TcpHandler::insertNode(UInt32 msgId, UInt32 msgLen)
{
	MsgNode * msgNode = new MsgNode(msgId, msgLen);
	if(!msgNode)
	{
		return false;
	}

	m_listMsgs.push_back(msgNode);

	m_pLastNode = msgNode;
	return true;
}