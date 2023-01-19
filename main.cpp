#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <graphics.h>

using namespace std;

#define MAX 20
#define FUNDAL BLUE
#define caine 1
#define vulpe 2
#define liber 0

int cul_caine=1;
int cul_vulpe=2;

int TablaDeJoc[MAX][MAX];
int stanga,sus,width,height,latura, numar;
int nrcastigaVulpe,nrcastigaCaini;

struct poz
{
    int x,y;
} pozvulpe;

int mod_joc=0;
bool ro;
int k=1;

void score();
void menuLimba();
void alegeLimba();
void help();
void alegeHelp();
void alege_buton();
void alegeModJoc();
bool cainiiCastiga();
void menuCaini();
void alege_castiga();
bool vulpeaCastiga();
void bordare();
void mutareVulpe();
void mutareCaine();
void punerePiesa(int linia, int coloana, int culoare);
void desen();
void menu();
void menuVulpe();
void PvC();
void strategia_de_baza();


int main()
{
    menuLimba();
    menu();
    alegeModJoc();

}

void score()
{
    setcolor(BLACK);
    setbkcolor(WHITE);
    if (ro==true)
    {
        char aux1[20]="VULPEA: ";
        aux1[8]=nrcastigaVulpe+'0';
        aux1[9]='\0';
        char aux2[20]={"CAINII: "};
        aux2[8]=nrcastigaCaini+'0';
        aux2[9]='\0';
        settextstyle(BOLD_FONT,HORIZ_DIR,1);
        settextjustify(1,1);
        outtextxy(100,sus+300,aux1);

        settextstyle(BOLD_FONT,HORIZ_DIR,1);
        settextjustify(1,1);
        outtextxy(100,sus+325,aux2);
    }
    else
    {
        char aux1[20]="FOX: ";
        aux1[5]=nrcastigaVulpe+'0';
        aux1[6]='\0';
        char aux2[20]="HOUNDS: ";
        aux2[8]=nrcastigaCaini+'0';
        aux2[9]='\0';
        settextstyle(BOLD_FONT,HORIZ_DIR,1);
        settextjustify(1,1);
        outtextxy(100,sus+300,aux1);

        settextstyle(BOLD_FONT,HORIZ_DIR,1);
        settextjustify(1,1);
        outtextxy(100,sus+325,aux2);
    }
}

void menuLimba()
{
    initwindow(300,300,"Language Menu");

    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(100,50,200,100);
    floodfill(101,51,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    settextjustify(1,1);
    outtextxy(150,75,"ROMANA");

    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(100,150,200,200);
    floodfill(101,151,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    settextjustify(1,1);
    outtextxy(150,175,"ENGLISH");

    alegeLimba();
}


void alegeLimba()
{
    int a,b;
    int DELAY = 50;

    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, a, b);



    if(a>100 && a<200 && b>50 && b<100)
        {
            closegraph();
            ro=true;
            mod_joc=0;
            alegeModJoc();
        }
    else
        if(a>100 && a<200 && b>150 && b<200)
    {
        mod_joc=0;
        closegraph();
        ro=false;
        alegeModJoc();
    }
    else
        alegeLimba();
}



void PvP()
{
    for(int i=1; i<=8; ++i)
        for(int j=1; j<=8; ++j)
        TablaDeJoc[i][j]=0;
    if(ro) initwindow(1200,600,"Cainii si Vulpea");
    else initwindow(1200,600,"Hounds and Fox");
    desen(); ///creare tablă de joc

    punerePiesa(1,4,cul_vulpe), TablaDeJoc[1][4]=vulpe; /// afișare vulpe pe tablă

    for(int i=1; i<=8; i+=2)
        punerePiesa(8,i,cul_caine), TablaDeJoc[8][i]=caine; /// afișare câini pe tablă
    bordare();
    do
    {
        mutareVulpe();
        if(vulpeaCastiga()) break;
        mutareCaine();
    }
    while(!(vulpeaCastiga() || cainiiCastiga()));
    if(vulpeaCastiga() || cainiiCastiga())
        closegraph();

    getch();
}



void PvC()
{
    for(int i=1; i<=8; ++i)
        for(int j=1; j<=8; ++j)
        TablaDeJoc[i][j]=0;
    if(ro) initwindow(1200,600,"Cainii si Vulpea");
    else initwindow(1200,600,"Hounds and Fox");
    desen(); ///creare tablă de joc

    punerePiesa(1,4,cul_vulpe), TablaDeJoc[1][4]=vulpe; /// afișare vulpe pe tablă

    for(int i=1; i<=8; i+=2)
        punerePiesa(8,i,cul_caine), TablaDeJoc[8][i]=caine; /// afișare câini pe tablă
    bordare();


    do
    {
        mutareVulpe();
        if(vulpeaCastiga()) break;
        strategia_de_baza();
    }
    while(!(vulpeaCastiga() || cainiiCastiga()));
    if(vulpeaCastiga() || cainiiCastiga())
        closegraph();

    getch();
}



void strategia_de_baza()
{
    int linia1,coloana1;

    for(linia1=8;linia1>=1;linia1--)
        for(coloana1=1;coloana1<=8;coloana1++)
            if(TablaDeJoc[linia1][coloana1]==caine)
            if(linia1%2==1)
                {if(TablaDeJoc[linia1-1][coloana1-1]==liber)
                {
                    TablaDeJoc[linia1-1][coloana1-1]=caine;
                    TablaDeJoc[linia1][coloana1]=liber;
                    punerePiesa(linia1,coloana1,WHITE);
                    punerePiesa(linia1-1,coloana1-1,cul_caine);
                    return;
                }}
            else
            {
                if(TablaDeJoc[linia1-1][coloana1+1]==liber)
                {
                    TablaDeJoc[linia1-1][coloana1+1]=caine;
                    TablaDeJoc[linia1][coloana1]=liber;
                    punerePiesa(linia1,coloana1,WHITE);
                    punerePiesa(linia1-1,coloana1+1,cul_caine);
                    return;
                }
            }
}






void alegeModJoc()
{
    if(mod_joc==0)
        menu();
    if(mod_joc==1)
        PvP();
    if(mod_joc==2)
        PvC();
    if(mod_joc==4)
        help();
    if(mod_joc==3) abort();
}

void help()
{
    initwindow(500,500);
    setcolor(WHITE);
    if(ro)
    {
        outtextxy(140,50,"Cum se joaca *Cainii si vulpea* ?");
        outtextxy(50,100,"PvP = Player vs player -> aici poti juca contra unui prieten.");
        outtextxy(50,120,"PvC = Player vs computer -> aici poti juca contra computerului.");
        outtextxy(50,140,"Pentru a muta o piesa, se da click stanga pe acesta, iar apoi ");
        outtextxy(40,160,"click stanga pe locul unde urmeaza sa fie mutata.");
        outtextxy(50,180,"Cainii se pot muta numai pe diagonala si mereu se muta inainte.");
        outtextxy(50,200,"Vulpea se poate muta numai pe diagonala, dar aceasta poate fi");
        outtextxy(40,220,"mutata si inainte si inapoi.");
        outtextxy(50,240,"Cainii vor castiga numai daca incoltesc vulpea.");
        outtextxy(50,260,"Vulpea va castiga numai in cazul in care ajunge pe una din pozitiile");
        outtextxy(40,280,"de unde au plecat cainii la inceputul jocului.");
    }
    else
    {
    outtextxy(140,50,"How to play *Hounds and Fox* ?");
    outtextxy(50,100,"PvP = Player vs player -> here you can play against your friend.");
    outtextxy(50,120,"PvC = Player vs computer -> here you can play against the computer.");
    outtextxy(50,140,"For moving a piece you left click on it and then  ");
    outtextxy(40,160," you left click on the spot where you want to put it.");
    outtextxy(50,180,"You can move the hounds only on diagonal, and only forward.");
    outtextxy(50,200,"You can move the fox only on diagional");
    outtextxy(40,220," and you can move it forward or back.");
    outtextxy(50,240,"The hounds will win only if they surround the fox.");
    outtextxy(50,260,"The fox will win only if it gets on one of the positions");
    outtextxy(40,280,"where the hounds are starting from.");
    }

    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(10,10,50,30);
    floodfill(11,11,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,1);
    settextjustify(1,1);
    outtextxy(30,25,"<-");

    alegeHelp();
    getch();
    closegraph();
}

void alegeHelp()
{
    int a,b;
    int DELAY = 50;

    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, a, b);


    if(a>10 && a<50 && b>10 && b<30)
        {
            closegraph();
            mod_joc=0;
            alegeModJoc();
        }
    else
        alegeHelp();


}

void menu()
{
    int xmijloc,ymijloc;

    initwindow(600,600,"Menu");
    xmijloc=getmaxx()/2;
    ymijloc=getmaxy()/2;
    settextstyle(BOLD_FONT,HORIZ_DIR,6);
    settextjustify(1,1);
    if(ro==true)
        outtextxy(xmijloc,50,"CAINII SI VULPEA");
    else
        outtextxy(xmijloc,50,"FOX AND HOUNDS");



    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(150,100,450,150);
    floodfill(151,101,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    settextjustify(1,1);
    outtextxy(xmijloc,135,"PvP");


    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(150,200,450,250);
    floodfill(151,201,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    settextjustify(1,1);
    outtextxy(xmijloc,235,"PvC");

    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(150,300,450,350);
    floodfill(151,301,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    settextjustify(1,1);
    if(ro==true)
        outtextxy(xmijloc,335,"IESIRE");
    else
        outtextxy(xmijloc,335,"EXIT");

    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(560,560,598,598);
    floodfill(561,561,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    settextjustify(1,1);
    outtextxy(580,585,"?");


    alege_buton();
    closegraph();

}
void desen()
{
    int i,j;
    numar=8;
    int black=0;
    width=550;
    height=350;
    latura=width/numar;
    sus=(getmaxy()-width)/2;
    stanga=(getmaxx()-height)/2;
    setbkcolor(FUNDAL);
    clearviewport();
    setcolor(BLUE);
    for (i=1; i<=numar; i++)
    {
        for (j=1; j<=numar; j++)
            if(black==1)
            {
                setcolor(RED);
                setfillstyle(SOLID_FILL,WHITE);
                rectangle(stanga+latura*(i-1),sus+latura*(j-1),stanga+latura*i,sus+latura*j);
                floodfill(stanga+latura*(i-1)+1,sus+latura*(j-1)+1,RED);
                black=0;
            }
            else
            {
                setcolor(RED);
                setfillstyle(SOLID_FILL,BLACK);
                rectangle(stanga+latura*(i-1),sus+latura*(j-1),stanga+latura*i,sus+latura*j);
                floodfill(stanga+latura*(i-1)+1,sus+latura*(j-1)+1,RED);
                black=1;
            }
        if(black==1)black=0;
        else black=1;
    }


    //caseta mesaje
    setcolor(BLACK);
    rectangle(0,sus,360,sus+50);
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(1,sus+1,BLACK);

    //score
    score();

}

void punerePiesa(int linia, int coloana, int culoare)
{
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;
    xmijloc=(x1+x2)/2;
    ymijloc=(y1+y2)/2;
    bar(xmijloc-31,ymijloc-31,xmijloc+31,ymijloc+31);
    if(culoare==cul_vulpe)
        readimagefile("fox.jpg",x1,y1,x2,y2);
    if(culoare==cul_caine)
        readimagefile("dog.jpg",x1,y1,x2,y2);
}

void mutareCaine()
{
    int linia1,coloana1,linia2,coloana2,x,y;
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    bool ok,click,piesa=false;

    do
    {
        click=false,ok=false;
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {


            setcolor(WHITE);
            setbkcolor(WHITE);
            if(ro==true)
                settextjustify(1,1),
                settextstyle(BOLD_FONT,HORIZ_DIR,1),
                outtextxy(180,sus+25,"nu poti muta aceasta piesa");
            else
                settextjustify(1,1),
                settextstyle(BOLD_FONT,HORIZ_DIR,1),
                outtextxy(180,sus+25,"you can't move this piece");


            click=true;
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            linia1=(y-sus)/latura+1;
            coloana1=(x-stanga)/latura+1;
            if (linia1>0 && linia1<9 && TablaDeJoc[linia1][coloana1]==caine) ok=true;
            if(TablaDeJoc[linia1-1][coloana1-1]!=liber && TablaDeJoc[linia1-1][coloana1+1]!=liber)
            {
                ok=0;
                setcolor(WHITE);
                setbkcolor(BLUE);
                if(ro==true)
                    settextjustify(1,1),
                    settextstyle(BOLD_FONT,HORIZ_DIR,1),
                    outtextxy(180,sus+25,"nu poti muta aceasta piesa");
                else
                    settextjustify(1,1),
                    settextstyle(BOLD_FONT,HORIZ_DIR,1),
                    outtextxy(180,sus+25,"you can't move this piece");
                piesa=true;
            }

        }
    }
    while (!(click && ok));
    Beep(2000,100);
    do
    {
        click=false;
        ok=false;
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            click=true;
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            linia2=(y-sus)/latura+1;
            coloana2=(x-stanga)/latura+1;
            if (linia2>0 && linia2<9 && TablaDeJoc[linia2][coloana2]==liber && abs(coloana1-coloana2)==1 && linia2-linia1==-1)
                ok=true;
        }
    }
    while ( !(click && ok) );
    Beep(3000,100);
    TablaDeJoc[linia1][coloana1]=0;
    TablaDeJoc[linia2][coloana2]=caine;
    punerePiesa(linia1,coloana1,WHITE);
    punerePiesa(linia2,coloana2,cul_caine);
}





void mutareVulpe()
{
    int linia1,coloana1,linia2,coloana2,x,y;
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    int click,ok;
    do
    {
        click=false;
        ok=false;
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            click=true;
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            linia1=(y-sus)/latura+1;
            coloana1=(x-stanga)/latura+1;
            if (linia1>0 && linia1<9 && TablaDeJoc[linia1][coloana1]==vulpe) ok=true;
        }
    }
    while ( !(click && ok) );
    Beep(2000,100);
    do
    {
        click=false;
        ok=false;
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            click=true;
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            linia2=(y-sus)/latura+1;
            coloana2=(x-stanga)/latura+1;
            if (linia2>0 && linia2<9 && TablaDeJoc[linia2][coloana2]==liber && abs(coloana1-coloana2)==1 && abs(linia2-linia1)==1)
                ok=true;
        }
        pozvulpe.x=linia2;
        pozvulpe.y=coloana2;

    }
    while ( !(click && ok) );
    Beep(3000,100);
    TablaDeJoc[linia1][coloana1]=0;
    TablaDeJoc[linia2][coloana2]=vulpe;
    punerePiesa(linia1,coloana1,WHITE);

    punerePiesa(linia2,coloana2,cul_vulpe);
}

void bordare()
{
    for(int i=0; i<10; ++i)
    {
        TablaDeJoc[0][i]=caine;
        TablaDeJoc[i][0]=caine;
        TablaDeJoc[9][i]=caine;
        TablaDeJoc[i][9]=caine;
    }
}


bool vulpeaCastiga()
{
    for(int i=1; i<=8; ++i)
        if(TablaDeJoc[8][i]==vulpe)
        {

            nrcastigaVulpe++;
            setbkcolor(FUNDAL);
            Beep(10000,300);
            closegraph();
            menuVulpe();
            return true;
            closegraph();
        }
    return false;
}



void alege_castiga()
{
    int a,b;
    int DELAY = 50;

    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, a, b);



    if(a>150 && a<450 && b>100 && b<150)
        {
            closegraph();
            alegeModJoc();
        }
    else
        if(a>150 && a<450 && b>200 && b<250)
    {
        nrcastigaCaini=0;
        nrcastigaVulpe=0;
        mod_joc=0;
        closegraph();
        alegeModJoc();
    }
    else
        if(a>150 && a<450 && b>300 && b<350)
    {
        mod_joc=3;
        closegraph();
        abort();
    }
    else
        alege_castiga();
}




void menuCaini()
{
    int xmijloc,ymijloc;

    initwindow(600,600);
    xmijloc=getmaxx()/2;
    ymijloc=getmaxy()/2;
    settextstyle(BOLD_FONT,HORIZ_DIR,6);
    settextjustify(1,1);
    if(ro==true)
        outtextxy(xmijloc,50,"CAINII AU CASTIGAT");
    else
        outtextxy(xmijloc,50,"HOUNDS WON");


    //first button
    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(150,100,450,150);
    floodfill(151,101,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    settextjustify(1,1);
    if(ro==true)
        outtextxy(xmijloc,135,"JOACA DIN NOU");
    else
        outtextxy(xmijloc,135,"PLAY AGAIN");

    //second button
    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(150,200,450,250);
    floodfill(151,201,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    settextjustify(1,1);
    if(ro==true)
        outtextxy(xmijloc,235,"MENIU");
    else
        outtextxy(xmijloc,235,"MENU");


    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(150,300,450,350);
    floodfill(151,301,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    settextjustify(1,1);
    if(ro==true)
        outtextxy(xmijloc,335,"IESIRE");
    else
        outtextxy(xmijloc,335,"EXIT");

    alege_castiga();
    closegraph();

}

void menuVulpe()
{
    int xmijloc,ymijloc;

    initwindow(600,600);
    xmijloc=getmaxx()/2;
    ymijloc=getmaxy()/2;
    settextstyle(BOLD_FONT,HORIZ_DIR,6);
    settextjustify(1,1);
    if(ro==true)
        outtextxy(xmijloc,50,"VULPEA A CASTIGAT");
    else
        outtextxy(xmijloc,50,"FOX WON");

    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(150,100,450,150);
    floodfill(151,101,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    settextjustify(1,1);
    if(ro==true)
        outtextxy(xmijloc,135,"JOACA DIN NOU");
    else
        outtextxy(xmijloc,135,"PLAY AGAIN");

    //second button
    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(150,200,450,250);
    floodfill(151,201,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    settextjustify(1,1);
    if(ro==true)
        outtextxy(xmijloc,235,"MENIU");
    else
        outtextxy(xmijloc,235,"MENU");


    setcolor(GREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    rectangle(150,300,450,350);
    floodfill(151,301,GREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    settextjustify(1,1);
    if(ro==true)
        outtextxy(xmijloc,335,"IESIRE");
    else
        outtextxy(xmijloc,335,"EXIT");

    alege_castiga();
    closegraph();

}

bool cainiiCastiga()
{
    if( TablaDeJoc[pozvulpe.x-1][pozvulpe.y-1]==caine &&
            TablaDeJoc[pozvulpe.x-1][pozvulpe.y+1]==caine &&
            TablaDeJoc[pozvulpe.x+1][pozvulpe.y-1]==caine &&
            TablaDeJoc[pozvulpe.x+1][pozvulpe.y+1]==caine )
    {
        nrcastigaCaini++;
        Beep(10000,300);
        closegraph();
        menuCaini();
        closegraph();
        return true;

    }
    return false;

}


void alege_buton()
{
    int a,b;
    int DELAY = 50;

    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, a, b);



    if(a>150 && a<450 && b>100 && b<150)
        mod_joc=1;
    else if(a>150 && a<450 && b>200 && b<250) mod_joc=2; /// nu avem inca facut modul de joc
    else if(a>150 && a<450 && b>300 && b<350) mod_joc=3; /// exit
    else if(a>560 && a<599 && b>560 && b<599) mod_joc=4; /// help
    else
        alege_buton();
}
