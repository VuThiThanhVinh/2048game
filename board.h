#ifndef BOARD_H
#define BOARD_H
#include<iostream>
#include<SDL2/SDL.h>
#include<ctime>
#include<cstdlib>
#include<SDL2/SDL_image.h>
#include<string>
#include <Windows.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
using namespace std;
TTF_Font*g_font_text=NULL;
const int StartWidth=39;
const int StartHeight=236;
const int WidthABox= 78;
const int HeightABox=80;
const int Space=16;
const int SCREEN_WIDTH= 437;
const int SCREEN_HEIGHT=700;
//danh sach cac anh
string path[]={
    "media/2_image.png","media/4_image.png","media/8_image.png",
    "media/16_image.png","media/32_image.png","media/64_image.png",
    "media/128_image.png","media/256_image.png","media/512_image.png",
    "media/1024_image.png","media/2048_image.png"
};

// anh tai cac o trong bang
SDL_Surface* Box[4][4]=
{NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL};

// toa do cac o trong bang
SDL_Rect Board[4][4];

void SetBoard()
{
    
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        { 
        Board[i][j].x=StartWidth+j*WidthABox+j*Space;
         Board[i][j].y=StartHeight+i*HeightABox+i*Space;
      
        }
    }
    
}

// khoi dong SDL va tao cua so
bool init();

// tai len phuong tien
bool loadMedia();

// giai phong phuong tien va tat SDL
void close();

//hien thi cua so
SDL_Window* window=NULL;

//lay ket qua cua viec doc tam anh image
    SDL_Surface* load_image =NULL;

//be mat cua cua so
SDL_Surface* screen_surface= NULL;

//anh background menu
SDL_Surface* BackgroundMenu=NULL;

//anh background main
SDL_Surface* BackgroundMain=NULL;

//anh background endgame
SDL_Surface* BackgroundEndgame=NULL;

//trinh xu ly su kien thoat de ket thuc ung dung
 SDL_Event e;

//luu anh cua cac hinh khoi can dung
SDL_Surface* imageX[11]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
class BaseObject
{
public:
  BaseObject();
  ~BaseObject();
  void Show(SDL_Surface* screen_surface);
  //bool LoadImg(const char* file_name);
  SDL_Rect ApplySurface(SDL_Surface* load_image, SDL_Surface* screen_surface, int x, int y);
  void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}
  SDL_Rect GetRect() const {return rect_;}
  SDL_Surface* GetObject() {return p_object_;}
protected:
  SDL_Rect rect_;
  SDL_Surface* p_object_;
};
BaseObject::BaseObject()
{
  rect_.x = 0;
  rect_.y = 0;
  p_object_ = NULL;
}

BaseObject::~BaseObject()
{
  if (p_object_ != NULL)
  {
    SDL_FreeSurface(p_object_);
  }
}
SDL_Rect BaseObject::ApplySurface(SDL_Surface* load_image, SDL_Surface* screen_surface, int x, int y)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(load_image, NULL, screen_surface, &offset);

  return offset;
}
void BaseObject::Show(SDL_Surface* screen_surface)
{
  if (p_object_ != NULL)
  {
    rect_ =  BaseObject::ApplySurface(p_object_, screen_surface, rect_.x, rect_.y);
  }
}
class TextObject : public BaseObject
{
public:
  enum TextColor
  {
    RED_TEXT  = 0,
    WHITE_TEXT = 1,
    BLACK_TEXT = 2,
  };

  TextObject()
{
  rect_.x = 30;
  rect_.y = 80;
  text_color_.r = 255;
  text_color_.g = 255;
  text_color_.b = 255;
}
 ~TextObject()
{

}
 
  void SetText(const std::string& text) {str_val_ = text;}
  void SetColor(const int& type)
{
  if (type == RED_TEXT)
  {
    SDL_Color color = {255, 0, 0};
    text_color_ = color;
  }
  else if (type == WHITE_TEXT)
  {
    SDL_Color color = {255, 255, 255};
    text_color_ = color;
  }
  else
  {
    SDL_Color color = {0, 0, 0};
    text_color_ = color;
  }
}

   void CreateGameText (TTF_Font* font, SDL_Surface* load_image)
{
  p_object_ = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
  Show(load_image);
}
private:

std::string str_val_;
SDL_Color text_color_;
};







bool init()
{
//co khoi tao
bool success= true;

//SDL_Init(Uint 32 flags) tra ve 0 neu thanh cong hoac tra ve gia tri am neu that bai
if(SDL_Init(SDL_INIT_VIDEO| SDL_INIT_AUDIO)<0)
{
cout<<"SDL could not initialize! SDL_Error:"<<SDL_GetError()<<endl;
success= false;
}
else{
    // tao cua so
    window=SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if(window==NULL){
        cout<<"Window could not be created! SDL_Error: "<<SDL_GetError()<<endl;
        success=false;
    }
    else
    {
        //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
            else
            {
                //Get window surface
                screen_surface = SDL_GetWindowSurface( window );
            }
        }
    }
    if(TTF_Init()<0) return false;
    g_font_text=TTF_OpenFont("Xerox Sans Serif Wide Bold.ttf",50);
    if(g_font_text==NULL) return false;
    return success;
}

SDL_Surface* LoadImage(string file_path){
    
    //toi uu hoa dinh dang tam anh
    SDL_Surface* optimize_image= NULL;

    //load anh 
    load_image=IMG_Load(file_path.c_str());
    if(load_image==NULL)
    {
    cout<<"Unalbe to load image, SDL_image Error "<<SDL_GetError()<<endl;
    }
    else
    {
        // sao chep anh sang be mat duoc chi dinh
       optimize_image=SDL_ConvertSurface(load_image,screen_surface->format,0);
        if(optimize_image==NULL) cout<<"Unable to optimize image, SDL Error "<<SDL_GetError()<<endl;
        
        //giai phong load_image
        else SDL_FreeSurface(load_image);
    }
    return optimize_image;
}
bool loadMedia(){
    //co khoi tao
    bool success=true;

     //tai be mat mac dinh( man hinh menu)
    BackgroundMenu=LoadImage("media/BackgroundMenu_image.png");
    
    //tai be mat main
    BackgroundMain=LoadImage("media/main_image.png");

    //tai len anh endgame
    BackgroundEndgame=LoadImage("media/endgame.png");

  for(int i=0;i<11;i++) imageX[i]=LoadImage(path[i]);
  
    if(BackgroundMain==NULL) 
    {
     cout<<"Failed to load background menu image"<<endl;
    success=false;
    }
 //Load music
    gMusic = Mix_LoadMUS( "media/KokuhakuNoYoru-Ayasa-5922559.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    

    
    gHigh = Mix_LoadWAV( "media/ringtonemakerwiz.com-2022-05-20.wav" );
    if( gHigh == NULL )
    {
        printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    
return success;

    

}
void close()
{
    

    //Free the sound effects
    Mix_FreeChunk( gScratch );
    Mix_FreeChunk( gHigh );
   
    gScratch = NULL;
    gHigh = NULL;
   
    
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
//giai phong be mat
SDL_FreeSurface(load_image);
load_image = NULL;

//huy cua so
SDL_DestroyWindow(window);
window = NULL;

//thoat khoi SDL
Mix_Quit();
IMG_Quit();
SDL_Quit();
}


#endif