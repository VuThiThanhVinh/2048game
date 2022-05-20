#include<vector>
#include "board.h"
#include<SDL2/SDL_ttf.h>
using namespace std;
bool quit=false;
int director;
//luu tru vi tri moi sinh so ngau nhien
vector <pair<SDL_Rect,SDL_Surface*>> ArrBoardMain;

// toa do cac anh da duoc sinh ngau nhien
vector<SDL_Rect>arrboard;

//luu tru toa do x y moi sinh so ngau nhien
pair<int,int> pos;

//bien kiem tra sinh so ngau nhien dau tien
bool check=false;

//bien kiem tra sinh so ngau nhien cua ham sinh so ngau nhien
bool test=true;

bool endgame=false;
bool backgroundendgame=false;
int count;
int checkscreen=0;
bool key=true;
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
            //cout<<"("<<b<<","<<j<<"),";
            pair<int,int> save;
            save.first=b;
            save.second=j;
            ArraySaveRect.push_back(save);
            
            }
                                    
        }
    }  
   // cout<<ArraySaveRect.size()-1<<endl;
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
             
        
            
     
        //cout<<line<<" "<<column<<endl;
   
    //return make_pair(line,column);
    }
}
bool CanMove(int i,int j,int NextI, int NextJ)
{   
    //tim kiem anh o toa do NextI NextJ cua ArrBoardMain
    int find=-1;
    for(int a=0;a<arrboard.size();a++)
    {
       if(arrboard[a].y==NextJ&&arrboard[a].x==NextI)
       {
           find=(NextI-StartWidth)/(Space+WidthABox);
           
         
       }
    }
   for(int a=0;a<arrboard.size();a++){
       if(arrboard[a].x==i&&arrboard[a].y==j){
           if(NextI<StartWidth||NextJ<StartHeight||NextI>(StartWidth+3*(Space+WidthABox))||NextJ>(StartHeight+3*(Space+HeightABox))) 
           return false;
       }
   }
   return true;
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
       
       // SDL_BlitSurface(BackgroundEndgame,NULL,screen_surface,NULL);

    }
    for(int i=0;i<arrboard.size();i++)
    if(ArrBoardMain[i].second==imageX[10]) win=true;
    
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
                             case SDLK_9:
                            //If there is no music playing
                            if( Mix_PlayingMusic() == 0 )
                            {
                                //Play the music
                                Mix_PlayMusic( gMusic, -1 );
                            }
                            //If music is being played
                            else
                            {
                                //If the music is paused
                                if( Mix_PausedMusic() == 1 )
                                {
                                    //Resume the music
                                    Mix_ResumeMusic();
                                }
                                //If the music is playing
                                else
                                {
                                    //Pause the music
                                    Mix_PauseMusic();
                                }
                            }
                            break;
                            
                            
                        }
                     }
                
                }
                 
                //Mix_PlayChannel( -1, gScratch, 0 );
                SDL_BlitSurface(load_image,NULL,screen_surface,NULL);
               

                if(check){
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