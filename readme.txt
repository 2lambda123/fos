1. search song
aaron@localhost webapi]$ python check_aihome.py -v song.ogg
{"recordId":"5649b42eac9fe20046000007","applicationId":"14476531938594b9","eof":1,"result":{"input":"���������»��ı���","semantics":{"request":{"domain":"����","action":"����","slotcount":2,"param":{"������":"����","������":"���»�"}}}}}

2. search wether
[aaron@localhost webapi]$ python check_aihome.py -v wether.ogg
{"recordId":"5649b436ac9fe20046000008","extra":{"����":{"����¶�":"3��C","����¶�":"11��C","����ָ��":{"�˶�ָ��":"�ϲ���(�Ƽ������и��������˶�)","��ðָ��":"�ٷ�(�����Խ��£���ð���ʽϵ�)","������ָ��":"����(��������Ϳ��SPF8-12��ɹ����Ʒ)"," ���ʶ�ָ��":"������(�����磬����ƫ�����������)","ϴ��ָ��":"����(���꣬��ˮ����ˮ��Ū�మ��)"},"����":"�޳�������","����":"����ת��ת���ѩ","����":"΢��"}},"applicationId":"14476531938594b9","eof":1,"output":"��������һ����ʮһ��ʮ���������� ����ת��ת���ѩ,����¶���3��C,����¶���11��C,�������޳�������,������΢��.","result":{"input":"��һ�±������������","semantics":{"request":{"domain":"����","action":"����","slotcount":2,"param":{"����":"20151117","����":"����"}}}}}


API�ӿ�˵��
1. ����websocket url ��Ĭ�ϰ���python�ű���ֵ���ɡ�
	  url='ws://%s:%s/%s/%s?applicationId=14476531938594b9&timestamp=%s&authId=%s&sig=%s&userId=test_yuyintianxia"' % (args.host,args.port,args.coretype,args.res,timestamp,authId,sig)
2. ����websocket����
		ws = websocket.create_connection(url)
3. �����ı�����TEXT��
		ws.send(text, websocket.ABNF.OPCODE_TEXT)
4. ���ͱ�����¼�����ݡ�BINARY��
	  ws.send(unit, websocket.ABNF.OPCODE_BINARY)
	 - ����һ���Է���ȫ�����ݡ��������ܻ�������ȴ���ʱ��ƫ����
	 - Ҳ����ÿһ����߼��ٺ��뷢��һ�Σ�������������ӿڡ�������ʵʱ�ϴ�¼�������Ƽ���
5. ������ֹ��Ϣ��һ������Ϊ0�Ķ�������Ϣ��
		ws.send('', websocket.ABNF.OPCODE_BINARY)	 	 	
6. ���շ������˵���Ӧ��json��ʽ��
	  result = ws.recv()				