#include <yzkgame.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib, "YZKGame.lib")

void moveBullet(int name,char direction,int v);//移动一个精灵按照一定方向速度
void normalkayup(unsigned char key);//获得用户一个按键
void moveSprite(int name);//根据按键移动精灵
BOOL isSpriteInsersect(int name1,int name2);//判断两个精灵是否接触
BOOL isSpriteInsersect2(int name1,int name2);//火焰是否打到boss头部 1为火焰2为boss
void chase(int name1,int name2);//让第二个精灵向第一个精灵移动
void jump(void*ari);//让精灵向上移动后落下
void monstAvance(void*ari);//创造个怪物并指定怪物怪物行动
int monst=1,huoyan=800,huoyan2=300,boss=12;//精灵
int direction=1;//方向
int hp=10;//boss血量
int mario=0;//mario的编号
void bossMove1(void*ari);//boss1的行动
void huoyanMove(void*ari);//火焰的行动
void attackjudge2(void*ari);//怪物与马里奥接触判定
void huoyan2Move(void*ari);//怪兽喷出的火焰//
void attackjudge1(void*ari);//怪物的受伤判定
void attackjudge3(void*ari);//boss的受伤判定
void xiaoguaiMove1(void*ari);//小怪的行动
void gameMain(void)
{

		char u[6];
		int l=0;//获得的金币数
	    int i;//跳跃时移动次数
		int nums[8]={1,2,3,4,5,6,7,8};
		int x,y;//马里奥的坐标
		int dis;//距离
		int image[20];
		int jincheng;//游戏中心循环的次数
		int kind=4;
		for(i=1;i<=20;i++)
		{image[i]=i;}
		setGameTitle("笨笨");
		setGameSize(1200,600);
		createImage(0,"game1.png");
		createText(0,"马里奥");
		setTextColor(0,1,1,0);
		setTextPosition(0,400,400);
		setTextFontSize(0,50);
		playSound("近藤浩治 - Side A - 纯音乐版.mp3",1);
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
						closeSound("近藤浩治 - Side A - 纯音乐版.mp3");
						playSound("近藤浩治 - SUPER MARIO BROS. 3 MEDLEY ARRANGE VERSION.mp3",1);
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
				closeSound("近藤浩治 - SUPER MARIO BROS. 3 MEDLEY ARRANGE VERSION.mp3");
				closeSound("近藤浩治 - Side A - 纯音乐版.mp3");
				playSound("高梨康治 - 薄暮.mp3",0);
				pauseGame(10000);
				exit(0);
	
			}
		}
		closeSound("近藤浩治 - SUPER MARIO BROS. 3 MEDLEY ARRANGE VERSION.mp3");
		playSound("光宗信吉 - 恋ってもどかしい - 纯音乐版.mp3",1);
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
		setText(0,"Author:袁坤");
		setTextPosition(0,400,400);
		setTextColor(0,0,1,1);
		setTextFontSize(0,20);
		showText(0);
		Sleep(1000);
		setText(1,"To my faivte girl:王倩");
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
BOOL isSpriteInsersect2(int name1,int name2)//name1为火焰，2为boss
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
		printf("错误");
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
	}///////////////////////////////////////////////////////////创造小怪
	else if(2==(int)ari)
		{createSprite(huoyan,"huoyan");
		asyncRun(huoyanMove,(void*)huoyan);
		huoyan++;
		}
	else if(3==(int)ari)//boss喷火
	{
		createSprite(huoyan2,"huoyan2");
		asyncRun(huoyan2Move,(void*)huoyan2);
		huoyan2++;
	}
	return;
}
void bossMove1(void*ari)//boss行为
{
	boss=(int)ari;
	setSpritePosition(boss,900,40);
	playSpriteAnimate(boss,"stand");
	asyncRun(attackjudge3,(void*)ari);//boss收到的欧攻击判定
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
void huoyanMove(void*ari)//马里奥释放的火球行动
{
	int fly;
	if(2==direction)
		{int huox=getSpriteX(0)+28;
		int huoy=getSpriteY(0)+20;
		setSpritePosition((int)ari,huox,huoy);
		playSpriteAnimate((int)ari,"rotate");
			for(fly=1;fly<=1000;fly++)//循环前进的次数
				{
					if(isSpriteVisible((int)ari))
						{
							moveBullet((int)ari,'d',3);
							Sleep(10);
						}
					else
						return;
				}
			hideSprite((int)ari);//结束后自动将火焰隐藏
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
void attackjudge1(void*ari)//第一阶段小怪收到攻击判定
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
								if(-1==lunhui)//打中三次后将其隐藏
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
void attackjudge2(void*ari)//怪物与马里奥接触判定
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
void xiaoguaiMove1(void*ari)//小怪的行为
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
		hideSprite((int)ari);//结束后将怪物隐藏
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
		hideSprite((int)ari);//结束后将怪物隐藏
	}
	return;
}
void attackjudge3(void*ari)//boss的受伤判定
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
void huoyan2Move(void*ari)//怪兽喷出的火焰//
{
	int fly;
	int huox=getSpriteX(boss)-88;
	int huoy=getSpriteY(boss)+190;
	setSpritePosition((int)ari,huox,huoy);
	playSpriteAnimate((int)ari,"advance");
	asyncRun(attackjudge2,(void*)ari);
	for(fly=1;fly<=1000;fly++)//循环前进的次数
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