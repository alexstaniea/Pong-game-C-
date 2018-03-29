#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
using namespace std;

enum dir{STOP=0,LEFT,UPLEFT,DOWNLEFT,RIGHT,UPRIGHT,DOWNRIGHT};



class ball
{
    int x,y;
    int origx,origy;
    dir direction;


public:
    ball(int pozx, int pozy)
    {
        x=pozx;
        y=pozy;
        origx=pozx;
        origy=pozy;
        direction=STOP;
    }

    void reset()
    {
        x=origx;
        y=origy;
        direction=STOP;
    }

    void changedir(dir d)
    {
        direction=d;
    }

    void random_dir()
    {
        direction=(dir)((rand()%6)+1);
    }

    void move()
    {
        switch(direction)
        {
            case STOP:
                        break;

            case LEFT:
                        x--;
                        break;

            case RIGHT:
                        x++;
                        break;

            case UPLEFT:
                        x--;
                        y++;
                        break;

            case UPRIGHT:
                        y++;
                        x++;
                        break;

            case DOWNLEFT:
                        y--;
                        x--;
                        break;

            case DOWNRIGHT:
                        y--;
                        x++;
                        break;

            default:
                        break;
        }
    }

    inline int getx(){return x;}
    inline int gety(){return y;}
    inline dir getdir(){return direction;}

    friend ostream& operator <<(ostream &o, ball &b)
    {
        o<<b.x<<","<<b.y<<","<<b.direction<<endl;
        return o;
    }

};




class paddle{

    int x,y;
    int origx,origy;

public:

    paddle(int pozx=0,int pozy=0)
    {
        origx=pozx;
        origy=pozy;
        x=pozx;
        y=pozy;
    }

    inline void reset(){x=origx; y=origy;}
    inline int getx(){return x;}
    inline int gety(){return y;}
    inline void moveup(){y++;}
    inline void movedown(){y--;}

    friend ostream& operator <<(ostream &o, paddle &b)
    {
        o<<b.x<<","<<b.y<<endl;
        return o;
    }


};


class game_manager
{

    int width,height;
    int score1,score2;
    char up1,up2,down1,down2;
    bool quit;
    ball *b;
    paddle *p1,*p2;

public:

    game_manager(int w,int h)
    {
        srand(time(NULL));
        quit=false;
        up1='w',down1='s';
        up2='i',down2='k';
        score1=score2=0;
        width=w; height=h;
        b=new ball(w/2,h/2);
        p1=new paddle(1,h/2-3);
        p2=new paddle(w-2,h/2-3);
    }

    void scoreup(paddle *player)
    {
        if(player == p1)
            score1++;

        if(player == p2)
            score2++;

        b->reset();
        p1->reset();
        p2->reset();
    }

    void draw()
    {
        system("cls");
        for(int i=0;i<width+2;i++)
            cout<<"\xB2";
        cout<<endl;

        for(int i=0;i<height;i++)
        {
           for(int j=0;j<width;j++)
               {
                   int bx=b->getx();
                   int by=b->gety();
                   int p1x=p1->getx();
                   int p1y=p1->gety();
                   int p2x=p2->getx();
                   int p2y=p2->gety();


                    if(j==0)
                        cout<<"\xB2";

                    if(bx==j && by==i)
                        cout<<"o";
                    else if(p1x==j && p1y==i)
                        cout<<"\xDB";
                    else if(p2x==j && p2y==i)
                        cout<<"\xDB";
                    else if(p1x==j && p1y+1 == i)
                        cout<<"\xDB";
                    else if(p1x==j && p1y+2 == i)
                        cout<<"\xDB";
                    else if(p1x==j && p1y+3 == i)
                        cout<<"\xDB";
                    else if(p2x==j && p2y+1 == i)
                        cout<<"\xDB";
                    else if(p2x==j && p2y+2 == i)
                        cout<<"\xDB";
                    else if(p2x==j && p2y+3 == i)
                        cout<<"\xDB";

                    else
                        cout<<" ";


                    if(j==width-1)
                       cout<<"\xB2";

               }
               cout<<endl;
        }


        for(int i=0;i<width+2;i++)
            cout<<"\xB2";

        cout<<"\n\n\nScore 1: "<<score1<<"\t\t\t"<<"Score 2: "<<score2<<endl;
    }

    void input()
    {
        b->move();

        int bx=b->getx();
        int by=b->gety();
        int p1x=p1->getx();
        int p1y=p1->gety();
        int p2x=p2->getx();
        int p2y=p2->gety();

        if(_kbhit())
        {
            char current=_getch();
            if(current == up1)
                if(p1y > 0)
                    p1->movedown();

            if(current == up2)
                if(p2y > 0)
                    p2->movedown();

            if(current == down1)
                if(p1y + 4 < height)
                    p1->moveup();

            if(current == down2)
                if(p2y + 4 < height)
                    p2->moveup();

            if(b->getdir() == STOP)
                b->random_dir();

            if(current == 'q')
                quit=true;
        }
    }

    void logic()
    {
        int bx=b->getx();
        int by=b->gety();
        int p1x=p1->getx();
        int p1y=p1->gety();
        int p2x=p2->getx();
        int p2y=p2->gety();

        for(int i=0;i<4;i++)
            if(bx == p1x + 1)
             if(by == p1y + i)
                b->changedir((dir)((rand()%3)+4));


        for(int i=0;i<4;i++)
            if(bx == p2x - 1)
             if(by == p2y + i)
                b->changedir((dir)((rand()%3)+1));

        if(by == 0)
            b->changedir(b->getdir()== DOWNRIGHT ? UPRIGHT : UPLEFT);

        if(by == height - 1)
            b->changedir(b->getdir()== UPRIGHT ? DOWNRIGHT : DOWNLEFT);

        if(bx == width -1)
            scoreup(p1);

        if(bx == 0)
            scoreup(p2);
    }

    void run()
    {
        while(!quit)
        {
            draw();
            input();
            logic();
        }
    }

    ~game_manager()
    {
        delete b,p1,p2;
    }
};

int main()
{
   game_manager p(40,20);
   p.run();
   return 0;

}
