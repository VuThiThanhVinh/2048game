#include<vector>
#include "board.h"
#include<SDL2/SDL_ttf.h>
using namespace std;
bool quit=false;

vector <pair<SDL_Rect,SDL_Surface*>> ArrBoardMain;

// toa do cac anh da duoc sinh ngau nhien
vector<SDL_Rect>arrboard;

//luu tru toa do x y moi sinh so ngau nhien
pair<int,int> pos;

//bien kiem tra sinh so ngau nhien dau tien
bool check=false;

//bien kiem tra sinh so ngau nhien cua ham sinh so ngau nhien
bool test=true;
// bien dung de check dieu kien end game la co du 16 anh tren cac o hay chua
bool endgame=false;
//khoa sinh so ngau nhien cua enter
int count_enter=0;

//bien dem so o con trong
int count;
//
bool backgroundendgame=false;

int checkscreen=0;
//khoa dung de khoa anh sinh ngau nhien luc mo chuong trinh
bool key=true;
//kiem tra da sinh anh 2048 hay chua,neu sinh anh 2048 thi se win
bool win=false;
// toa do di kem voi anh tai cac o
pair<SDL_Rect,SDL_Surface*>arr[4][4];

//tao mang de quan ly bang chinh trong chuong trinh
void SetArr()
{
    SetBoard();
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++) 
        {
            arr[i][j].first=Board[i][j];
            arr[i][j].second=Box[i][j];
        }
    }
}


//sinh anh o vi tri ngau nhien
void generateUnoccupiedPostion()
{   //mang luu vi tri con trong de sinh so ngau nhien
    vector<pair<int,int>>ArraySaveRect;


         for(int b=0;b<4;b++)
    {
         for(int j=0;j<4;j++)
        {
          bool check1=false;
         for(int k=0;k<arrboard.size();k++)
            {
              if(arrboard[k].x==arr[b][j].first.x&&arrboard[k].y==arr[b][j].first.y) check1=true;

            }
         if(!check1){ arr[b][j].second=NULL;
            
            pair<int,int> save;
            save.first=b;
            save.second=j;
            ArraySaveRect.push_back(save);
            
            }
                                    
        }
    }  
   
    if(ArraySaveRect.size()==0) endgame=true;
    else{
        endgame=false;
          srand(time(NULL));
          //chon phan tu cua mang chua cac o null de sinh anh ngau nhien
          int ran=rand()%(ArraySaveRect.size());

            int line=ArraySaveRect[ran].first;
            int  column=ArraySaveRect[ran].second;
             
           
                SDL_Rect v;
                v.y=StartHeight+line*HeightABox+line*Space;

                v.x=StartWidth+column*WidthABox+column*Space;
               
             // toa do anh moi sinh ngau nhien
             arrboard.push_back(v);
             pair<SDL_Rect,SDL_Surface*>z;
             z.first=v;
            z.second=imageX[0];
             ArrBoardMain.push_back(z);

    }
}
bool CanMove(int i,int j,int NextI, int NextJ)
{   

   for(int a=0;a<arrboard.size();a++){
       if(arrboard[a].x==i&&arrboard[a].y==j){
           if(NextI<StartWidth||NextJ<StartHeight||NextI>(StartWidth+3*(Space+WidthABox))||NextJ>(StartHeight+3*(Space+HeightABox))) 
           return false;
       }
   }
   return true;
}


void Move_Down(){
                            if(!key){
                             for(int j=StartHeight+3*(Space+HeightABox);j>=StartHeight;j-=Space+HeightABox)
                                {
                                      for(int i=StartWidth;i<=StartWidth+3*(Space+WidthABox);i+=Space+WidthABox)
                            {
                               
                                     int NextI=i;
                                     int NextJ=j+Space+HeightABox;

                                    //kiem tra xem toa do i j co nam trong nhung diem da co hay khong
                                     bool check2=false;
                                     for(int k=0;k<arrboard.size();k++)
                                     {
                                         if(arrboard[k].x==i&&arrboard[k].y==j) check2=true;
                                     }
                                     
                                     //kiem tra xem diem co toa do NextI NextJ co nam trong nhung diem da co hay khong
                                     bool check3=false;
                                     for(int k=0;k<arrboard.size();k++)
                                     {
                                         if(arrboard[k].x==NextI&&arrboard[k].y==NextJ) check3=true;
                                     }
                                    if(check2&&CanMove(i,j,NextI,NextJ))
                                     { 
                                         if(!check3)
                                         {
                                                
                                             for(int c=0;c<arrboard.size();c++)
                                             {
                                                 if(arrboard[c].x==i&&arrboard[c].y==j)
                                                    arrboard[c].y+=Space+HeightABox;
                                                   
                                             }
                                                
                                         }
                                         else
                                         {    //luu chi so cua anh ngau nhien o vi tri i j      
                                             int m1;
                                                //luu chi so cua anh ngau nhien o vi tri NextI NextJ 
                                            int m2;
                                                //luu chi so cua anh ngau nhien giong nhau o vi tri gan nhau i j va NextI NextJ
                                             int m3;
                                               
                                                
                                             for(int c=0;c<arrboard.size();c++)
                                             { 
                                                 if(arrboard[c].x==i&&arrboard[c].y==j)m1=c;
                                                
                                             }
                                                
                                             for(int c=0;c<arrboard.size();c++)
                                             { 
                                                 if(arrboard[c].x==NextI&&arrboard[c].y==NextJ)m2=c;
                                                  
                                             }
                                            
                                             
                                             if(ArrBoardMain[m1].second==ArrBoardMain[m2].second)
                                             {
                                                 
                                                 for(int o=0;o<11;o++) if (ArrBoardMain[m1].second==imageX[o]) m3=o;
                                                  ArrBoardMain[m1].second=NULL;
                                                
                                                 ArrBoardMain[m2].second=NULL;
                                                   
                                                
                                                  ArrBoardMain[m1].second=imageX[m3+1];
                                                  arrboard[m2].x=0;
                                                  arrboard[m2].y=0;
                                                  arrboard[m1].y+=Space+HeightABox;
                                                   
                                             }
                                            
                                           
                                        }
                                        
                                     }
                                }
                                
                            }
                           
                           
                            
                             generateUnoccupiedPostion();
                           }
                   

}
void Move_Up(){
                if(!key){
                                   for(int j=StartHeight;j<=StartHeight+3*(Space+HeightABox);j+=Space+HeightABox)
                                {
                            for(int i=StartWidth;i<=StartWidth+3*(Space+WidthABox);i+=Space+WidthABox)
                            {
                               
                                     int NextI=i;
                                     int NextJ=j-Space-HeightABox;

                                    //kiem tra xem toa do i j co nam trong nhung diem da co hay khong
                                     bool check2=false;
                                     for(int k=0;k<arrboard.size();k++)
                                     {
                                         if(arrboard[k].x==i&&arrboard[k].y==j) check2=true;
                                     }
                                     
                                     //kiem tra xem diem co toa do NextI NextJ co nam trong nhung diem da co hay khong
                                     bool check3=false;
                                     for(int k=0;k<arrboard.size();k++)
                                     {
                                         if(arrboard[k].x==NextI&&arrboard[k].y==NextJ) check3=true;
                                     }
                                     if(check2&&CanMove(i,j,NextI,NextJ))
                                     {
                                         if(!check3)
                                         {
                                             for(int c=0;c<arrboard.size();c++)
                                             {
                                                 if(arrboard[c].x==i&&arrboard[c].y==j)
                                                    arrboard[c].y-=Space+HeightABox;
                                             }
                                             
                                         }
                                         else
                                         {    //luu chi so cua anh ngau nhien o vi tri i j      
                                             int m1;
                                                //luu chi so cua anh ngau nhien o vi tri NextI NextJ 
                                            int m2;
                                                //luu chi so cua anh ngau nhien giong nhau o vi tri gan nhau i j va NextI NextJ
                                             int m3;
                                               
                                                
                                             for(int c=0;c<arrboard.size();c++)
                                             { 
                                                 if(arrboard[c].x==i&&arrboard[c].y==j)m1=c;
                                                
                                             }
                                                
                                             for(int c=0;c<arrboard.size();c++)
                                             { 
                                                 if(arrboard[c].x==NextI&&arrboard[c].y==NextJ)m2=c;
                                                  
                                             }
                                            
                                             
                                             if(ArrBoardMain[m1].second==ArrBoardMain[m2].second)
                                             {
                                                 
                                                 for(int o=0;o<11;o++) if (ArrBoardMain[m1].second==imageX[o]) m3=o;
                                                  ArrBoardMain[m1].second=NULL;
                                                
                                                 ArrBoardMain[m2].second=NULL;
                                            
                                                  ArrBoardMain[m1].second=imageX[m3+1];
                                                  arrboard[m2].x=0;
                                                  arrboard[m2].y=0;
                                                  arrboard[m1].y-=Space+HeightABox;
                                                   
                                             }
                                            
                                           
                                        }
                                        
                                     }
                                }
                                
                            }
                             
                             generateUnoccupiedPostion();
                             }
}
void Move_Right(){
if(!key){
                         for(int j=StartHeight;j<=StartHeight+3*(Space+HeightABox);j+=Space+HeightABox)
                                {
                            for(int i=StartWidth+3*(Space+WidthABox);i>=StartWidth;i-=Space+WidthABox)
                            {
                               
                                     int NextI=i+Space+WidthABox;
                                     int NextJ=j;

                                    //kiem tra xem toa do i j co nam trong nhung diem da co hay khong
                                     bool check2=false;
                                     for(int k=0;k<arrboard.size();k++)
                                     {
                                         if(arrboard[k].x==i&&arrboard[k].y==j) check2=true;
                                     }
                                     
                                     //kiem tra xem diem co toa do NextI NextJ co nam trong nhung diem da co hay khong
                                     bool check3=false;
                                     for(int k=0;k<arrboard.size();k++)
                                     {
                                         if(arrboard[k].x==NextI&&arrboard[k].y==NextJ) check3=true;
                                     }
                                     if(check2&&CanMove(i,j,NextI,NextJ))
                                     {
                                         if(!check3)
                                         {
                                             for(int c=0;c<arrboard.size();c++)
                                             {
                                                 if(arrboard[c].x==i&&arrboard[c].y==j)
                                                    arrboard[c].x+=Space+WidthABox;
                                             }
                                             
                                         }
                                         else
                                         {    //luu chi so cua anh ngau nhien o vi tri i j      
                                             int m1;
                                                //luu chi so cua anh ngau nhien o vi tri NextI NextJ 
                                            int m2;
                                                //luu chi so cua anh ngau nhien giong nhau o vi tri gan nhau i j va NextI NextJ
                                             int m3;
                                               
                                                
                                             for(int c=0;c<arrboard.size();c++)
                                             { 
                                                 if(arrboard[c].x==i&&arrboard[c].y==j)m1=c;
                                                
                                             }
                                                
                                             for(int c=0;c<arrboard.size();c++)
                                             { 
                                                 if(arrboard[c].x==NextI&&arrboard[c].y==NextJ)m2=c;
                                                  
                                             }
                                            
                                             
                                             if(ArrBoardMain[m1].second==ArrBoardMain[m2].second)
                                             {
                                                 
                                                 for(int o=0;o<11;o++) if (ArrBoardMain[m1].second==imageX[o]) m3=o;
                                                  ArrBoardMain[m1].second=NULL;
                                                
                                                 ArrBoardMain[m2].second=NULL;
                                            
                                                  ArrBoardMain[m1].second=imageX[m3+1];
                                                  arrboard[m2].x=0;
                                                  arrboard[m2].y=0;
                                                  arrboard[m1].x+=Space+WidthABox;
                                                   
                                             }
                                            
                                           
                                        }
                                        
                                     }
                                }
                                
                            }
                             
                             generateUnoccupiedPostion();
                             }
                             
}
void Move_Left(){
if(!key){
                            for(int j=StartHeight;j<=StartHeight+3*(Space+HeightABox);j+=Space+HeightABox)
                                {
                            for(int i=StartWidth;i<=StartWidth+3*(Space+WidthABox);i+=Space+WidthABox)
                            {
                               
                                     int NextI=i-Space-WidthABox;
                                     int NextJ=j;

                                    //kiem tra xem toa do i j co nam trong nhung diem da co hay khong
                                     bool check2=false;
                                     for(int k=0;k<arrboard.size();k++)
                                     {
                                         if(arrboard[k].x==i&&arrboard[k].y==j) check2=true;
                                     }
                                     
                                     //kiem tra xem diem co toa do NextI NextJ co nam trong nhung diem da co hay khong
                                     bool check3=false;
                                     for(int k=0;k<arrboard.size();k++)
                                     {
                                         if(arrboard[k].x==NextI&&arrboard[k].y==NextJ) check3=true;
                                     }
                                     if(check2&&CanMove(i,j,NextI,NextJ))
                                     {
                                         if(!check3)
                                         {
                                             for(int c=0;c<arrboard.size();c++)
                                             {
                                                 if(arrboard[c].x==i&&arrboard[c].y==j)
                                                    arrboard[c].x-=Space+WidthABox;
                                             }
                                             
                                             
                                         }
                                         else
                                         {    //luu chi so cua anh ngau nhien o vi tri i j      
                                             int m1;
                                                //luu chi so cua anh ngau nhien o vi tri NextI NextJ 
                                            int m2;
                                                //luu chi so cua anh ngau nhien giong nhau o vi tri gan nhau i j va NextI NextJ
                                             int m3;
                                               
                                                
                                             for(int c=0;c<arrboard.size();c++)
                                             { 
                                                 if(arrboard[c].x==i&&arrboard[c].y==j)m1=c;
                                                
                                             }
                                                
                                             for(int c=0;c<arrboard.size();c++)
                                             { 
                                                 if(arrboard[c].x==NextI&&arrboard[c].y==NextJ)m2=c;
                                                  
                                             }
                                            
                                             
                                             if(ArrBoardMain[m1].second==ArrBoardMain[m2].second)
                                             {
                                                 
                                                 for(int o=0;o<11;o++) if (ArrBoardMain[m1].second==imageX[o]) m3=o;
                                                  ArrBoardMain[m1].second=NULL;
                                                
                                                 ArrBoardMain[m2].second=NULL;
                                            
                                                  ArrBoardMain[m1].second=imageX[m3+1];
                                                  arrboard[m2].x=0;
                                                  arrboard[m2].y=0;
                                                  arrboard[m1].x-=Space+WidthABox;
                                                   
                                             }
                                            
                                           
                                        }
                                        
                                     }
                                }
                                
                            }
                            
                             generateUnoccupiedPostion();
                             
                            }
}
void Endgame()
{
    int count=0;
    backgroundendgame=false;
    bool checkallboard= false;
    for(int i=0;i<arrboard.size();i++)
    {
        checkallboard=false;
        for(int j=0;j<arrboard.size();j++){
           
           if((arrboard[i].x==arrboard[j].x+Space+WidthABox&&arrboard[i].y==arrboard[j].y
           || arrboard[i].x==arrboard[j].x-Space-WidthABox&&arrboard[i].y==arrboard[j].y
           ||arrboard[i].x==arrboard[j].x&&arrboard[i].y==arrboard[j].y+Space+HeightABox
           ||arrboard[i].x==arrboard[j].x&&arrboard[i].y==arrboard[j].y-Space-HeightABox)
           && arrboard[i].x!=0&&arrboard[i].y!=0&&arrboard[j].x!=0&&arrboard[j].y!=0
           &&ArrBoardMain[i].second==ArrBoardMain[j].second
           )
          count++;

        }

    }
  
    //cout<<count<<endl;
    if(count==0)
    {
       backgroundendgame=true;
    }
    for(int i=0;i<arrboard.size();i++)
    if(ArrBoardMain[i].second==imageX[10]) win=true;
    
}
void PlayGame(){

                //xu ly cac su kien dang doi, tra ve 1 neu co su kien dang cho xu ly, tra ve 0 neu khong co su kien dang can duoc xu ly
                while(SDL_PollEvent(&e)!=0)
                {
                //yeu cau thoat cua nguoi choi game
                    if(e.type==SDL_QUIT)
                    {
                        quit =true;
                    }
                     else if(e.type==SDL_KEYDOWN)
                    {
                        switch( e.key.keysym.sym )
                        {
                           
                            case SDLK_KP_ENTER:
                                load_image=BackgroundMain;
                                check=true;
                                key=false;
                                count_enter++;
                               
                            break;
                            
                            case SDLK_DOWN:
                            Mix_PlayChannel( -1, gHigh, 0 );
                           Move_Down();
                            break;
                             case SDLK_UP:
                             Mix_PlayChannel( -1, gHigh, 0 );
                                Move_Up();

                            break;
                             case SDLK_RIGHT:
                             Mix_PlayChannel( -1, gHigh, 0 );
                             Move_Right();
                            break;
                            
                            case SDLK_LEFT:
                            Mix_PlayChannel( -1, gHigh, 0 );
                            Move_Left();
                            break;
                            
                            
                            
                        }
                     }
                
                }
                 
                
                SDL_BlitSurface(load_image,NULL,screen_surface,NULL);
               

                if(check&&count_enter==1){
                generateUnoccupiedPostion();
                   Mix_PlayMusic( gMusic, -1 );
                check=false;
                }
                      
               for(int i=0;i<arrboard.size();i++){
                   if(arrboard[i].x!=0&&arrboard[i].y!=0)
                SDL_BlitSurface(ArrBoardMain[i].second,NULL,screen_surface,&arrboard[i]);

               }
                Endgame();
                if((endgame&&backgroundendgame)||win==true)  
                        SDL_BlitSurface(BackgroundEndgame,NULL,screen_surface,NULL);
                  //cap nhat be mat
                SDL_UpdateWindowSurface(window);
            
}

int main(int argc, char* args[] ) 
{
 

    // khoi tao SDL

    SetArr();
    
    if(!init())
    {
        cout<<"Failed to initialize"<<endl;

    }
    else
    {
        if(!loadMedia())
        {
            cout<<"Failed to load media"<<endl;
        }
        else
        {
            //co vong lap chinh
             quit=false;
            //dat be mat hien tai mac dinh la background menu
            load_image=BackgroundMenu;
       
            while(!quit)
            {
            
            PlayGame();
            
            }

        }
    }

}