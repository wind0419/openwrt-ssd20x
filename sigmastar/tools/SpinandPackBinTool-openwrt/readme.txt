
һ�������ļ���Ҫ����������

1.��ִ�г��� SstarMakeBin

2.��ʼ���ļ�PNAND.INI(pnand), SPINAND.INI(spinand),�����ɵ���pnand��image����spinand��image

3.Ҫ����bin�ļ���scripts�ļ�

ִ������bin������Ϊ

./SstarMakeBin -n  PNAND.INI       //����pnand��image
./SstarMakeBin -n  SPINAND.INI     //����spinand��image

����XXX.INI�ļ�˵��

[path]                               //����image��script������bin�����·��
root_directory=./
image_directory=pnand/               //����image��λ�ã��ǵñ�©��\��
script_file=auto_update_pnand.txt    //��һ��ִ�е�scripts�ļ�
outpath=./

[nand]                               //����nand�����ͣ���id
nandtype=PNAND                       //�����pnand����ΪPNAND,�����spinand����ΪSPINAND����Сд������
#nandtype=SPINAND
nandid=0x98-0xF1-0x80-0x15-0xF2      //Ҫ���ɵ�image�ܵİ����ϵ�flash��id��
//nandid=0xC2-0x12

[env]                               //���û������������ͺͱ������������֣��Ա�����bin�ļ�ʱ�ܹ����滷������
env_type=NANDRAW                    //Ŀǰ����ֱ�Ӵ���nandflash�У����Զ�����ΪNANDRAW 
env_part=ENV                        //�����������������֣�Ҫ��mtdparts�еĻ���������������һ��
#env_volume=MPOOL
#env_offset=0

[cis]                               //����nni�ļ���pni�ļ�����Ҫ��Ϊ��tool������ʱload��Ӧ�ļ���ʼ��flash�����Ĳ���
ecctype=10                          //ʹ��Ĭ��ֵ�ͺ�
nni=NANDINFO.nni                    //pnandʹ��.nni�ļ�
#nni=SPINANDINFO.sni                //spinandʹ��.sni�ļ� 
pni=PARTINFO.pni                    //�����ļ�
#ppm=PAIRPAGEMAP_v2.ppm             //��ʱû���õ�

[fcie]                              //�˴���Ҫ��������pnand����ecc�����ͣ�spinand�ò�����Ŀǰ��������fcie5
type=fcie5

[boot]
#boottype=BFN
#miu=bfn_miu.bin

[rawdata]
#type=nand

����auto_update.txt˵��

����Ҫ���ǵ�һ�У�����������������mtdparts��ֵһ��
dynpart nand0:0x60000@0x140000(IPL0),0x60000(IPL1),0x60000(IPL_CUST0),0x60000(IPL_CUST1),0xC0000(UBOOT0),0xC0000(UBOOT1),0x60000(ENV),0x560000(KERNEL),0x560000(RECOVERY),-(UBI)

ָ������Ҫ���ص�ȫ���Ų����ļ�
estar images/mscript/nand.es

ִ����������ɵ�bin�ļ�Ϊnand.bin,�����ļ�Ϊsnchk.def���������ļ�������¼����¼��ʱ����õ�
������Ҫ��Ҫһ�㣬���ɵ�pnand bin�ļ��ǰ���oob���ģ�spinand��bin�ļ��ǲ�����oob���ģ�spinand��oob����spinand�Լ����ɵģ�������¼��ʱ��ǵø���flahs���ͣ��򿪻��ǹر�oobѡ��

Ŀǰ�ļ��ļ���ֻ֧��tftpָ����Լǵ��޸�һ�½ű�

�ġ��ļ�ִ��(����)˳��

SstarMakeBin->SPINAND.INI->auto_update_spinand.txt->spinand.es->scripts folder file
spinand_example_imgֻ�Ƿ��������һ������image���ǿͻ���Ҫ���ɵ�����bin����Ҫ��image�ļ����ͻ�ʵ������ʱ�������Լ���image�ļ��滻��

�塢����ʱ�ļ��

1. �����ִ������binʱ�б����ȼ��һ���Ƿ���ִ�е����֧�֣�����sd�������ű���Ҫ��Ϊtftp�Ľű���ʽ
2. �Ƿ�ִ����һЩsave������±����˷�����Ϣ�����·�����Ϣ����auto_update_spinand.txt��ָ���ķ�����һ��
3. �������¼���������ܲ����������ȸ��ݷ�����Ϣ��������ɵ�bin�ļ���Ӧƫ�Ƶ�ַ�����ļ���Ϣ�Ƿ���ȷ������IPL�ķ���ƫ��Ϊ0x140000���������ɵ�bin�ļ���ַ0x140000λ�ô����ļ������Ƿ�ΪIPL�ļ�������
4. �����¼����¼ʱoob���Ƿ�disable
5. ��flash tool���߷ֱ�dump��������flash��ʼ����IPL����ƫ�ƴ���IPL_CUST����ƫ�ƴ���UBOOT����ƫ�ƴ���kernel����ƫ�ƴ��Ĳ����ļ��Ա��Ƿ�����¼��bin�ļ�һ��
