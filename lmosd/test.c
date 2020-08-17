#include <string.h>
#include <stdlib.h>
#include "lmosd.h"

//ע:������Ĭ�ϴ������ gb2312 encoder ���ַ���,
//���� sourceinsight ������ gb2312���� ��ʾ����Ȼ���ܽ�������.
int main()
{
 	int ret = 0;
	ret = Lm_start_font_file("./font/asc_16x16.zk", LAN_ASCALL);
	ret = Lm_start_font_file("./font/jtzw_16x16.zk", LAN_JTZW);
	if(ret < 0)
	{
		printf("Lm_start_font_file function failed !\n");
		exit(-1);
	}

	int yuv_wdith = 960;
	int yuv_hight = 720;
	int size = yuv_wdith*yuv_hight*3/2;
	char *yuv_buf = malloc(size);
	FILE *fd = fopen("960x720_YUV420.yuv", "rb");
	ret = fread(yuv_buf, 1, size, fd);
	if(ret < 0)
	{
		free(yuv_buf);
		printf("fread yuv file failed !\n");
		exit(-1);
	}
		
	char buff[1024*2] = {'\0'};
	font_t  ft;
	
	ft.cd.x = 10;
	ft.cd.y = 10;
	ft.cd.w = 10;
	ft.cd.h = 10;
	ft.fontcolor  = 0x0000ff; //0x00ff00; //字体颜色: 绿色
	ft.bordcolor  = -1; //背景�?
	ft.backGround =	BGC_NO; // 无背景色,则�?�明
	ft.isAddEdge  = 0;
	
	ft.iSize    = 1;
	ft.bdunmp   = 1;
	ft.dumpfile = "./test1.yuv";
	ft.str = buff;
	char *temp0 = "2019��12��15��, This is a  new day !;";
	memcpy(ft.str, temp0, strlen(temp0));
	
	ft.yuv_ty = 1;//0:yuv422, 1:yuv420, 这里不细�?.
	ft.yuv_w  = yuv_wdith;
	ft.yuv_h  = yuv_hight;
	ft.ysize  = yuv_wdith *yuv_hight;
	ft.yuvadd = yuv_buf; // 要叠加的yuv地址
	ret = Lm_set_string(&ft);
	if(ret < 0)
	{
		Lm_destroy_lmosd();
		free(yuv_buf);
		printf("fread yuv file failed !\n");
		exit(-1);
	}

	ft.cd.x = 10;
	ft.cd.y = 200;
	ft.cd.w = 10;
	ft.cd.h = 10;
	ft.fontcolor  = 0x0000ff; //0xbc1717; //字体颜色: 猩红�?
	ft.bordcolor  = -1;//0x00; //背景�?
	ft.backGround =	BGC_NO;//BGC_DO;
	ft.isAddEdge  = 0;
	
	ft.iSize    = 1;
	ft.bdunmp   = 1;
	ft.dumpfile = "./test1.yuv";
	ft.str 	    = buff;
	char *temp1 = "զ����������ҷ��������ָ����й�ϵ��";
	memcpy(ft.str, temp1, strlen(temp1));

	//在同�?张yuv上写osd,这里不再重复赋�??.
	ft.yuvadd = yuv_buf;
	ret = Lm_set_string(&ft);
	if(ret < 0)
	{
		Lm_destroy_lmosd();
		free(yuv_buf);
		printf("fread yuv file failed !\n");
		exit(-1);
	}

	ft.cd.x = 560;
	ft.cd.y = 190;
	ft.cd.w = 10;
	ft.cd.h = 10;
	ft.fontcolor  = 0x00;//0x7f00ff; //字体颜色: 中石板蓝�?
	ft.bordcolor  = -1;//0x215E21; //背景�?
	ft.backGround =	BGC_NO;//BGC_DO;
	ft.isAddEdge  = 0;
	ft.iSize    = 1;
	ft.bdunmp   = 1;
	ft.dumpfile = "./test1.yuv";
	ft.str = buff;
	char *temp2 = "        ���� ����������                \n"
 				  "ǧ��ݺ����ӳ�죬ˮ��ɽ������硣\n"
 				  "�ϳ��İٰ�ʮ�£�����¥̨�����С�\n";
	memcpy(ft.str, temp2, strlen(temp2));
	
	ft.yuvadd  = yuv_buf;
	ret = Lm_set_string(&ft);
	if(ret < 0)
	{
		Lm_destroy_lmosd();
		free(yuv_buf);
		printf("fread yuv file failed !\n");
		exit(-1);
	}

	//�?毁lmosd资源.	
	Lm_destroy_lmosd();
	free(yuv_buf);

	return 0;
}
