#include <yzkgame.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib, "YZKGame.lib")

void moveBullet(int name,char direction,int v);//�ƶ�һ�����鰴��һ�������ٶ�
void normalkayup(unsigned char key);//����û�һ������
void moveSprite(int name);//���ݰ����ƶ�����
BOOL isSpriteInsersect(int name1,int name2);//�ж����������Ƿ�Ӵ�
BOOL isSpriteInsersect2(int name1,int name2);//�����Ƿ��bossͷ�� 1Ϊ����2Ϊboss
void chase(int name1,int name2);//�õڶ����������һ�������ƶ�
void jump(void*ari);//�þ��������ƶ�������
void monstAvance(void*ari);//��������ﲢָ����������ж�
int monst=1,huoyan=800,huoyan2=300,boss=12;//����
int direction=1;//����
int hp=10;//bossѪ��
int mario=0;//mario�ı��
void bossMove1(void*ari);//boss1���ж�
void huoyanMove(void*ari);//������ж�
void attackjudge2(void*ari);//����������½Ӵ��ж�
void huoyan2Move(void*ari);//��������Ļ���//
void attackjudge1(void*ari);//����������ж�
void attackjudge3(void*ari);//boss�������ж�
void xiaoguaiMove1(void*ari);//С�ֵ��ж�
void gameMain(void)
{

		char u[6];
		int l=0;//��õĽ����
	    int i;//��Ծʱ�ƶ�����
		int nums[8]={1,2,3,4,5,6,7,8};
		int x,y;//����µ�����
		int dis;//����
		int image[20];
		int jincheng;//��Ϸ����ѭ���Ĵ���
		int kind=4;
		for(i=1;i<=20;i++)
		{image[i]=i;}
		setGameTitle("����");
		setGameSize(1200,600);
		createImage(0,"game1.png");
		createText(0,"�����");
		setTextColor(0,1,1,0);
		setTextPosition(0,400,400);
		setTextFontSize(0,50);
		playSound("���ٺ��� - Side A - �����ְ�.mp3",1);
		pauseGame(2000);
		hideText(0);
		for(i=1;i<=20;i++)
		{
			createImage(image[i],"qiangbi.png");
			setImagePosition(image[i],((i-1)*60),0);
		}
		createSprite(mario,"mario");
		setSpritePosition(mario,0,40);
		playSpriteAnimate(mario,"stand");
		onNormalKeyUp(normalkayup);
		for(jincheng=1;jincheng<=400;jincheng++)
		{
			if (0>hp)
			{
				break;
			}
			if(isSpriteVisible(mario))
			{
				moveSprite(mario);
				pauseGame(10);
				if(400==jincheng)
				{
					if(15==kind)
					{
						closeSound("���ٺ��� - Side A - �����ְ�.mp3");
						playSound("���ٺ��� - SUPER MARIO BROS. 3 MEDLEY ARRANGE VERSION.mp3",1);
					}
					asyncRun(monstAvance,(void*)kind);
					kind++;
					jincheng=1;
				}
			}
			else
			{
				playSpriteAnimate(mario,"sleep");
				showSprite(mario);
				setText(0,"GAME OVER");
				Sleep(500);
				hideSprite(mario);
				showText(0);
				closeSound("���ٺ��� - SUPER MARIO BROS. 3 MEDLEY ARRANGE VERSION.mp3");
				closeSound("���ٺ��� - Side A - �����ְ�.mp3");
				playSound("���濵�� - ��ĺ.mp3",0);
				pauseGame(10000);
				exit(0);
	
			}
		}
		closeSound("���ٺ��� - SUPER MARIO BROS. 3 MEDLEY ARRANGE VERSION.mp3");
		playSound("�����ż� - ���äƤ�ɤ����� - �����ְ�.mp3",1);
		setSpriteFlipX(0,TRUE);
		Sleep(5000);
		createSprite(299,"rainee");
		setSpritePosition(299,1100,40);
		playSpriteAnimate(299,"walk");
		playSpriteAnimate(0,"walk");
		while (1)
		{
			int mariox=getSpriteX(0);
			int raineex=getSpriteX(299);
			raineex-=2;
			mariox+=2;
			if (570>mariox)
			{
				setSpritePosition(mario,mariox,40);
			}
			else
			{
				playSpriteAnimate(mario,"stand");
			}
			if (600<raineex)
			{
				setSpritePosition(299,raineex,40);
			}
			else
			{
				playSpriteAnimate(299,"stand");
			}
			if (600>=raineex&&570<=mariox)
			{
				break;
			}
			
			Sleep(10);
		}
		playSpriteAnimate(299,"stand");
		createImage(299,"heart.png");
		setImagePosition(299,600-25,100);				
		setText(0,"CONGRATULATIONS ON YOU");
		showText(0);
		createText(1,"It is said that people who play the game can find a girlfriend.");
		setTextColor(1,0,1,1);
		setTextFontSize(1,20);
		setTextPosition(1,300,350);
		Sleep(10000);
		hideText(0);
		hideText(1);
		Sleep(1000);
		setText(0,"Author:Ԭ��");
		setTextPosition(0,400,400);
		setTextColor(0,0,1,1);
		setTextFontSize(0,20);
		showText(0);
		Sleep(1000);
		setText(1,"To my faivte girl:��ٻ");
		setTextPosition(1,400,350);
		showText(1);
		Sleep(5000);
		while (1)
		{
			Sleep(10000);
		}
		return;
}

int main(void)
{

	rpInit(gameMain);
  
	return 0;
}
void moveSprite(int name)
{        int mv=getPressedKeyCode();
		 int x,y;
		 x=getSpriteX(0);
		 y=getSpriteY(0);
		
		if(RP_KEY_DOWN==mv);
		
		
		else if(RP_KEY_LEFT==mv)
		{
			if(x>2)
			{
				x-=2;
				if(40==y)
				{playSpriteAnimate(name,"walk");}
				setSpriteFlipX(0,FALSE);
				setSpritePosition(0,x,y);
				direction=1;
			}
		}
		else if(RP_KEY_RIGHT==mv)
			{   if(1150>x)
				{
					x+=2;
					if(40==y)
					playSpriteAnimate(name,"walk");
					setSpriteFlipX(0,TRUE);
					setSpritePosition(0,x,y);
					direction=2;
		        }
		}
		
		else if(0==mv&&y==40)
		{playSpriteAnimate(name,"stand");
		
		}
		else;
		
		
}
		
BOOL isSpriteInsersect(int name1,int name2)
{
	int x1=getSpriteX(name1);
	int x2=getSpriteX(name2);
	int y1=getSpriteY(name1);
	int y2=getSpriteY(name2);
	BOOL a1=x2>x1+2*getSpriteWidth(name1)/3;
	BOOL a2=x1>x2+2*getSpriteWidth(name2)/3;
	BOOL b1=y1>y2+getSpriteHeight(name2);
	BOOL b2=y2>y1+getSpriteHeight(name1);
	BOOL insersect=(!a1&&!a2&&!b1&&!b2);
	return insersect;

}
BOOL isSpriteInsersect2(int name1,int name2)//name1Ϊ���棬2Ϊboss
{
	int x1=getSpriteX(name1);
	int x2=getSpriteX(name2);
	int y1=getSpriteY(name1);
	int y2=getSpriteY(name2);
	BOOL a1=x2>x1+2*getSpriteWidth(name1)/3;
	BOOL a2=x1>x2+2*getSpriteWidth(name2)/3;
	BOOL b1=y1>y2+getSpriteHeight(name2);
	BOOL b2=(y2+167)>(y1+getSpriteHeight(name1));
	BOOL insersect=(!a1&&!a2&&!b1&&!b2);
	return insersect;

}
void moveBullet(int name,char direction,int v)
{ 
	int j=getSpriteX(name);
	int k=getSpriteY(name);
	switch (direction)
	{
	case 'w':
		k+=v;
		setSpritePosition(name,j,j);
		break;
	case 's':
		k-=v;
		setSpritePosition(name,j,k);
		break;
	case 'a':
		j-=v;
		setSpritePosition(name,j,k);
		break;
	case 'd':
		j+=v;
		setSpritePosition(name,j,k);
		break;
	default:
		printf("����");
		break;
	}
	return;
}

void normalkayup(unsigned char key)
{
	if(isSpriteVisible(0))
		{
		if(' '==key)
		asyncRun(jump,(void*)1);
		else if('x'==key)
			asyncRun(monstAvance,(void*)2);
		}
	return;
}
void jump(void*ari)
{
	int i=1;
	int y=getSpriteY(0);
	if(40==y)
	{
		for(i=1;i<=250;i++)
		{int y=getSpriteY(0);
		int x=getSpriteX(0);
		if(y>550)
			break;
		y++;
		playSpriteAnimate(0,"jump");
		setSpritePosition(0,x,y);
		Sleep(2);
		}
		for(i=1;i<=600;i++)
		{int y=getSpriteY(0);
		int x=getSpriteX(0);
		if(y<=40)
			break;
		y--;
		setSpritePosition(0,x,y);
		Sleep(2);
		}
	}
	else;
	return;
}
void monstAvance(void*ari)
{
	if(15==(int)ari)
		{createSprite(monst,"boss1");
		asyncRun(bossMove1,(void*)monst);
		monst++;
		}
	else if((int)ari>3&&(int)ari!=15)
	{
		createSprite(monst,"xiaoguai1");
		asyncRun(xiaoguaiMove1,(void*)monst);
		monst++;
	}///////////////////////////////////////////////////////////����С��
	else if(2==(int)ari)
		{createSprite(huoyan,"huoyan");
		asyncRun(huoyanMove,(void*)huoyan);
		huoyan++;
		}
	else if(3==(int)ari)//boss���
	{
		createSprite(huoyan2,"huoyan2");
		asyncRun(huoyan2Move,(void*)huoyan2);
		huoyan2++;
	}
	return;
}
void bossMove1(void*ari)//boss��Ϊ
{
	boss=(int)ari;
	setSpritePosition(boss,900,40);
	playSpriteAnimate(boss,"stand");
	asyncRun(attackjudge3,(void*)ari);//boss�յ���ŷ�����ж�
	asyncRun(attackjudge2,(void*)ari);
	while(1)
	{
		if (1!=isSpriteVisible(boss))
		{
			return;
		}
		playSpriteAnimate(boss,"stand");	
		asyncRun(monstAvance,(void*)3);
		Sleep(1500);
		asyncRun(monstAvance,(void*)3);
		Sleep(1500);
		asyncRun(monstAvance,(void*)3);
		Sleep(3000);
		playSpriteAnimate(boss,"walk");
		moveBullet(boss,'a',12);
		Sleep(2000);
	}
	return;
}
void huoyanMove(void*ari)//������ͷŵĻ����ж�
{
	int fly;
	if(2==direction)
		{int huox=getSpriteX(0)+28;
		int huoy=getSpriteY(0)+20;
		setSpritePosition((int)ari,huox,huoy);
		playSpriteAnimate((int)ari,"rotate");
			for(fly=1;fly<=1000;fly++)//ѭ��ǰ���Ĵ���
				{
					if(isSpriteVisible((int)ari))
						{
							moveBullet((int)ari,'d',3);
							Sleep(10);
						}
					else
						return;
				}
			hideSprite((int)ari);//�������Զ�����������
			return;
		}
	else

		{int huox=getSpriteX(0);
		int huoy=getSpriteY(0)+20;
		setSpritePosition((int)ari,huox,huoy);
		playSpriteAnimate((int)ari,"rotate");
			for(fly=1;fly<=1000;fly++)
				{int bao;
					moveBullet((int)ari,'a',3);
					for(bao=1;bao<monst;bao++)
					{
						if(isSpriteVisible(bao))
							{
								if(isSpriteInsersect(bao,(int)ari))
									{   hideSprite((int)ari);
											break;
									}
							}
					}
				Sleep(10);
				}
			hideSprite((int)ari);
			return;
		}
}
void attackjudge1(void*ari)//��һ�׶�С���յ������ж�
{
	int change;
	int lunhui=2;
	char*xiaoguai[3]={"died","one","two"};
	while(1)
	{
		for(change=1;change<=huoyan-800;change++)
				{
					if(isSpriteVisible(change+799))
						{
							if(isSpriteInsersect(change+799,(int)ari))
								{
									hideSprite(change+799);
								playSpriteAnimate((int)ari,xiaoguai[lunhui]);
								lunhui--;
								if(-1==lunhui)//�������κ�������
									{
										Sleep(1000);
										hideSprite((int)ari);
										return;
									}
								break;
								}
						}
				}
		Sleep(1);
	}
}
void attackjudge2(void*ari)//����������½Ӵ��ж�
{
	while(1)
	{
		if(isSpriteVisible((int)ari))
		{
			if(isSpriteInsersect(0,(int)ari))
			{
			
				hideSprite(0);
				break;
			}

		}
		Sleep(1);
	}
}
void xiaoguaiMove1(void*ari)//С�ֵ���Ϊ
{
	int xiaoguai1;
	if(12>(int)ari)
	{
		setSpritePosition((int)ari,1150,40);
		playSpriteAnimate((int)ari,"three");
		asyncRun(attackjudge1,(void*)ari);
		asyncRun(attackjudge2,(void*)ari);
		for(xiaoguai1=1;xiaoguai1<=1200;xiaoguai1++)
			{
				if(isSpriteVisible((int)ari))
					{
					moveBullet((int)ari,'a',1);
					Sleep(5);
					}
				else
					return;
		
			}
		hideSprite((int)ari);//�����󽫹�������
	}
	else
	{
		int x=getSpriteX(boss)-40;
		setSpritePosition((int)ari,x,40);
		playSpriteAnimate((int)ari,"three");
		asyncRun(attackjudge1,(void*)ari);
		asyncRun(attackjudge2,(void*)ari);
		for(xiaoguai1=1;xiaoguai1<=1200;xiaoguai1++)
			{
				if(isSpriteVisible((int)ari))
					{
					moveBullet((int)ari,'a',1);
					Sleep(5);
					}
				else
					return;
		
			}
		hideSprite((int)ari);//�����󽫹�������
	}
	return;
}
void attackjudge3(void*ari)//boss�������ж�
{
	int judge=0;
	while (1)
	{
		for (judge=1;judge<=huoyan-820;judge++)
		{
			if (isSpriteVisible(judge+819))
			{
				if (isSpriteInsersect(judge+819,(int)ari))
				{
					
					if (isSpriteInsersect2(judge+819,(int)ari))
					{
						hideSprite(judge+819);
						hp--;
						if (0>hp)
						{
							hideSprite(boss);
							return;
						}
					}
					hideSprite(judge+819);
				}
			}
		}
		Sleep(1);
	}
}
void huoyan2Move(void*ari)//��������Ļ���//
{
	int fly;
	int huox=getSpriteX(boss)-88;
	int huoy=getSpriteY(boss)+190;
	setSpritePosition((int)ari,huox,huoy);
	playSpriteAnimate((int)ari,"advance");
	asyncRun(attackjudge2,(void*)ari);
	for(fly=1;fly<=1000;fly++)//ѭ��ǰ���Ĵ���
			{
				if(isSpriteVisible((int)ari))
					{
						moveBullet((int)ari,'a',3);
						Sleep(10);
					}
				else
					return;
	        }
	hideSprite((int)ari);
	return;	
}