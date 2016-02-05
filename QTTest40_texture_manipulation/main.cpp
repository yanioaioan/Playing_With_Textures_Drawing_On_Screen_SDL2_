/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>

#include <iostream>
#include <cstring>


//Screen dimension constants
const int SCREEN_WIDTH = 720*2;
const int SCREEN_HEIGHT = 576;
TTF_Font *gFont;
//typedef enum {FALSE,TRUE} boolean;

bool leftMouseButtonDown=false;
const int WHITE=255;
int windowId=-1;

void handleEvent( SDL_Event& e );

//Texture wrapper class
class LTexture
{
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile( std::string path );

        //Loads texture
        bool loadTexture();

        #ifdef _SDL_TTF_H
        //Creates image from font string
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor , int x, int y);
        #endif

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );

        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        void update( );

        //Gets image dimensions
        int getWidth();
        int getHeight();

        //Pixel manipulators
        bool lockTexture();
        bool unlockTexture();
        void* getPixels();
        int getPitch();

        //The actual hardware texture
        SDL_Texture* mTexture;
        SDL_Texture* mToolsTexture;

    private:

        void* mPixels;
        void* mToolsPixels;
        int mPitch;
        int mToolsPitch;


        //Image dimensions
        int mWidth;
        int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
SDL_Window* toolsWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;
SDL_Renderer* gRenderer2 = NULL;


//Scene textures
LTexture gFooTexture;
SDL_Surface* formattedSurface;
SDL_Surface* gScreenSurface;
LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    mPixels = NULL;
    mToolsPixels = NULL;
    mPitch = 0;
    mToolsPitch = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}
bool LTexture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

//    //Load image at specified path
//    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
//    if( loadedSurface == NULL )
//    {
//        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
//    }
//    else
//    {
        //Convert surface to display format

//        formattedSurface = SDL_ConvertSurface( loadedSurface,  SDL_GetWindowSurface(gWindow)->format, NULL );
//        formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_ARGB8888, NULL );

//        if( formattedSurface == NULL )
//        {
//            printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
//        }
//        else
        {


            //Create blank streamable texture
            newTexture = SDL_CreateTexture( gRenderer,SDL_GetWindowPixelFormat( gWindow ), SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT );
            if( newTexture == NULL )
            {
                printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Lock texture for manipulation
                SDL_LockTexture( newTexture, NULL, &mPixels, &mPitch );

//                //Copy loaded/formatted surface pixels
//                memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );



//                //Unlock texture to update
                SDL_UnlockTexture( newTexture );
                mPixels = NULL;

                //Get image dimensions
                mWidth = /*formattedSurface->w*/ SCREEN_WIDTH;
                mHeight = /*formattedSurface->h*/ SCREEN_HEIGHT;
            }

//            //Get rid of old formatted surface
//            SDL_FreeSurface( formattedSurface );
        }

        //Get rid of old loaded surface
//        SDL_FreeSurface( loadedSurface );
//    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}



bool LTexture::loadTexture()
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;
    SDL_Texture* toolsTexture = NULL;

        {
            //Create blank streamable texture
            newTexture = SDL_CreateTexture( gRenderer,SDL_GetWindowPixelFormat( gWindow ), SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT );
            toolsTexture = SDL_CreateTexture( gRenderer2,SDL_GetWindowPixelFormat( toolsWindow ), SDL_TEXTUREACCESS_STREAMING, 200, 200 );

            if( newTexture == NULL || toolsTexture == NULL)
            {
                printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Lock texture for manipulation
                SDL_LockTexture( newTexture, NULL, &mPixels, &mPitch );
                SDL_LockTexture( toolsTexture, NULL, &mToolsPixels, &mToolsPitch );

//                //Copy loaded/formatted surface pixels
//                memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

                //set backgrounf to white
//                memset(mPixels, WHITE , SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

//                memset(mToolsPixels, 0 , 100 * 100 * sizeof(Uint32));



                //Unlock texture to update
                SDL_UnlockTexture( newTexture );
                mPixels = NULL;
                SDL_UnlockTexture( toolsTexture );
                mToolsPixels = NULL;

                //Get image dimensions
                mWidth =  SCREEN_WIDTH;
                mHeight = SCREEN_HEIGHT;
            }

        }



    //Return success
    mTexture = newTexture;
    mToolsTexture = toolsTexture;
    return mTexture != NULL && mToolsTexture !=NULL;
}



#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor,int x, int y )
{

    /*Create 100 surfaces blit one to the existing one*/

    //Get rid of preexisting texture
//    free();

     gFont = TTF_OpenFont("arial.ttf", 10);
    //Render text surface

     SDL_Surface* textSurface;
//     for(int i=0;i<100;i++)
     {
     textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
//    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(gFont, textureText.c_str(), textColor ,300);

        SDL_Rect textLocation = { x, y, 8, 10 };
    //SDL_BlitSurface(textSurface, NULL, formattedSurface, &textLocation);





    //Then create a texture from the "final textSurface"

    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;


            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

            //do not clear the screen
//            SDL_RenderClear( gRenderer );

            SDL_SetTextureColorMod(mTexture,textColor.r,textColor.g,textColor.b);
            SDL_RenderCopy(gRenderer,mTexture, NULL, /*&charLocation*/  &textLocation);



        }


    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }



     }
    TTF_CloseFont(gFont);
    //Get rid of old surface
    SDL_FreeSurface( textSurface );

    //Return success
    return mTexture != NULL;
}
#endif

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
        mPixels = NULL;
        mPitch = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

//void LTexture::update()
//{
//    SDL_UpdateTexture((SDL_Texture*)this, NULL, formattedSurface->pixels, formattedSurface->pitch);
//}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
//    //Set rendering space and render to screen
//    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//    SDL_Rect renderQuad2 = { 0, 0, 100, 100 };

//    //Set clip rendering dimensions
//    if( clip != NULL )
//    {
//        renderQuad.w = clip->w;
//        renderQuad.h = clip->h;
//    }

//    //Render to screen
//    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );

//    if( clip != NULL )
//    {
//        renderQuad2.w = clip->w;
//        renderQuad2.h = clip->h;
//    }

//    SDL_RenderCopyEx( gRenderer, mToolsTexture, clip, &renderQuad2, angle, center, flip );

}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool LTexture::lockTexture()
{
    bool success = true;

    //Texture is already locked
    if( mPixels != NULL )
    {
        printf( "Texture is already locked!\n" );
        success = false;
    }
    //Lock texture
    else
    {
        if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 )
        {
            printf( "Unable to lock texture! %s\n", SDL_GetError() );
            success = false;
        }
    }

    return success;
}

bool LTexture::unlockTexture()
{
    bool success = true;

    //Texture is not locked
    if( mPixels == NULL )
    {
        printf( "Texture is not locked!\n" );
        success = false;
    }
    //Unlock texture
    else
    {
        SDL_UnlockTexture( mTexture );
        mPixels = NULL;
        mPitch = 0;
    }

    return success;
}

void* LTexture::getPixels()
{
    return mPixels;
}

int LTexture::getPitch()
{
    return mPitch;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
        //Grab window identifier
        windowId = SDL_GetWindowID( gWindow );

        toolsWindow = SDL_CreateWindow( "Tool Box", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, 0 );
        windowId = SDL_GetWindowID( toolsWindow );


        if( gWindow == NULL || toolsWindow ==NULL)
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {

            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            gRenderer2 = SDL_CreateRenderer( toolsWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
//            gRendererTools = SDL_CreateRenderer( toolsWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL  )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
//                SDL_SetRenderDrawColor( gRendererTools, 0xFF, 0x00, 0x00, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }


                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                { return false; }



            }
        }
    }

    return success;
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

int powerof(int x,int y)
{
    int tmp=x;
    for(int i=1;i<y;i++)
    {

        tmp*=x;
    }
    return tmp;
}


std::string getGrayShade(int avRGBVal)
{
    std::string asciichar = " ";


    if (avRGBVal >= 225)
    {
        asciichar = "`";
    }
    else if (avRGBVal >= 200)
    {
        asciichar = ".";
    }
    else if (avRGBVal >= 175)
    {
        asciichar = ":";
    }
    else if (avRGBVal >= 150)
    {
        asciichar = "!";
    }
    else if (avRGBVal >= 125)
    {
        asciichar = "o";
    }

    else if (avRGBVal >= 100)
    {
        asciichar = "*";
    }
    else if (avRGBVal >= 75)
    {
        asciichar = "8";
    }
    else if (avRGBVal >= 50)
    {
        asciichar = "%";
    }
    else if (avRGBVal >= 25)
    {
        asciichar = "#";
    }
    else
    {
        asciichar = "@";
    }

    return asciichar;
}


bool loadMedia()
{
    //Loading success flag
    bool success = true;


    //Load foo' texture
//    if( !gFooTexture.loadFromFile( "lion.png" ) )
    if(!gFooTexture.loadTexture())
    {
        printf( "Failed to load corner texture!\n" );
        success = false;
    }
    else
    {
        //Lock texture
//        if( !gFooTexture.lockTexture() )
//        {
//            printf( "Unable to lock Foo' texture!\n" );
//        }
        //Manual color key
//        else
//        {
            //Get pixel data
//            Uint32* pixels = (Uint32*)gFooTexture.getPixels();//formattedSurface->pixels;
//            int pixelCount = ( gFooTexture.getPitch() / 4 ) * gFooTexture.getHeight();


            //Map colors
//            Uint32 colorKey = SDL_MapRGB( SDL_GetWindowSurface( gWindow )->format, 0, 0xFF, 0xFF );
//            Uint32 transparent = SDL_MapRGBA( SDL_GetWindowSurface( gWindow )->format, 0xFF, 0xFF, 0xFF, 0x00 );

//            Uint32 colorKey = SDL_MapRGB( formattedSurface->format, 0, 0xFF, 0xFF );
//            Uint32 transparent = SDL_MapRGBA( formattedSurface->format, 0XFF, 0XFF, 0XFF, 0xFF );

//                        for( int i = 0; i < pixelCount; ++i )
//                        {
//                            if( pixels[ i ] == colorKey )
//                            {
//                                pixels[ i ] = transparent;
//                            }
//                        }



            //Averagine by block
            //Color key pixels
            //int powerof2=powerof(2,10);//for a formattedSurface->w/64 block pixel width this should produce 8 blocks of 8 pixels
//            int blockDivider=64;
//            int block_width=formattedSurface->w/blockDivider;
//            int block_height=formattedSurface->h/blockDivider;

//            std::string blockCharacterString;
//            //For each block every block_width pixels
//            for(int bx = block_width; bx <= formattedSurface->w;  bx += block_width)
//            {
//                //For each block every block_height pixels
//                for(int by = block_height; by <= formattedSurface->h; by += block_height)
//                {

//                    //total sum of Red,Green,Blue channel values
//                    float sumR=0;
//                    float sumG=0;
//                    float sumB=0;

//                    //CurrentPixel
//                    Uint32 pixel;

//                    int blockPixelcounter=0;
//                    //For each block every block_height pixels
//                    for(int x = bx-block_width; x < bx; x++)
//                    {
//                        for(int y = by-block_height; y < by; y++)
//                        {

//                            Uint8 red ;
//                            Uint8 green ;
//                            Uint8 blue ;
//                            pixel=pixels[x + y * formattedSurface->w];

//                            SDL_GetRGB( pixel, formattedSurface->format ,  &red, &green, &blue );


//                            sumR=sumR+red;
//                            sumG=sumG+green;
//                            sumB= sumB+blue;
//                            blockPixelcounter++;


//                        }

//                    }//square block end


//                    //get the average chanel color
//                    int avR=sumR/blockPixelcounter; int avG=sumG/blockPixelcounter; int avB=sumB/blockPixelcounter;

//                    //Gray Scale it - based on each rgb value
////                    Uint8 v = 0.212671f * red  + 0.715160f * green  + 0.072169f * blue;

//                    //Gray Scale it - based on the average rgb value
//                    Uint8 v = 0.212671f * avR  + 0.715160f * avG  + 0.072169f * avB;
//                    //pixel = (0xFF << 24) | (v << 16) | (v << 8) | v;



                    /*
                     * instead of modifying pixel in the line above,
                      we can query the character which is going to replace this block based
                      on the average grayscale value of the 3 R,G,B channels
                     */
//                    int avRGBValue=v /*  OR (avR+avG+avB)/3  */;
//                    blockCharacterString+=getGrayShade(avRGBValue);




//                    //iterate and replace all pixel color values with this average grayscal value
//                    for(size_t x = bx-block_width; x < bx; x++)
//                    {
//                        for(size_t y = by-block_height; y < by; y++)
//                        {
//                            //manually change the color of the pixel
//                                    pixel = (0xFF << 24) | (red << 16) | (green << 8) | blue;
//                            pixels [(formattedSurface->w* y)+x ] = pixel;
//                        }

//                    }//square block end replacing values



//                            //Avegage Block Color
//                            sumR+=red; sumG+=green; sumB+=blue;
//                            pixels [(gFooTexture.getWidth()* by)+bx ] = 255;


                    //Create a texture (appropriate chosen character, appropriately colored) for each block of pixels at bx,by to be replaced
//                    SDL_Color AV_BLOCK_COLOR = {avR,avG,avB};

                    /*
                     * and now we can create a texture of the characters in the blockCharacterString
                     */
//                    gFooTexture.loadFromRenderedText(getGrayShade(avRGBValue),AV_BLOCK_COLOR,bx,by);

//                }

                //when we reach the end of each row of pixels we add a new line \n
                //blockCharacterString+="\n";


            }

            //At the end. Get pixels of the surface associated with the gRenderer (formattedSurface)
            //save the image
//            Uint32 * finaltexturePixels = (Uint32 *)formattedSurface->pixels;
//            SDL_RenderReadPixels(gRenderer, &formattedSurface->clip_rect, formattedSurface->format->format, finaltexturePixels, formattedSurface->w * formattedSurface->format->BytesPerPixel);
//            SDL_Surface* saveSurface = SDL_CreateRGBSurfaceFrom(finaltexturePixels, formattedSurface->w, formattedSurface->h,
//                                                                formattedSurface->format->BitsPerPixel,
//                                                                formattedSurface->w * formattedSurface->format->BytesPerPixel,
//                                                                formattedSurface->format->Rmask, formattedSurface->format->Gmask,
//                                                                formattedSurface->format->Bmask, formattedSurface->format->Amask);


//            SDL_SaveBMP(saveSurface, "MYASCIICOLOREDIMAGE.bmp");


            //Get rid of old formatted surface
//            SDL_FreeSurface( formattedSurface );

            //Unlock texture
//            gFooTexture.unlockTexture();
//        }
//    }

    return success;
}

void close()
{
    //Free loaded images
    gFooTexture.free();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


void handleEvent( SDL_Event& e )
{
    //If an event was detected for this window
//    if( e.type == SDL_WINDOWEVENT && e.window.windowID == 2 )
    {
        //Caption update flag
//        bool updateCaption = false;

        switch( e.window.event )
        {
            //Window appeared
            case SDL_WINDOWEVENT_SHOWN:
//            mShown = true;
            break;

            //Window disappeared
            case SDL_WINDOWEVENT_HIDDEN:
//            mShown = false;
            break;

            //Get new dimensions and repaint
            case SDL_WINDOWEVENT_SIZE_CHANGED:
//            mWidth = e.window.data1;
//            mHeight = e.window.data2;
//            SDL_RenderPresent( gRenderer );
//            SDL_RenderPresent( gRenderer2 );
            break;

            //Repaint on expose
            case SDL_WINDOWEVENT_EXPOSED:
//            SDL_RenderPresent( gRenderer );
//            SDL_RenderPresent( gRenderer2 );
            break;

            //Mouse enter
            case SDL_WINDOWEVENT_ENTER:
//            mMouseFocus = true;
//            updateCaption = true;
            break;

            //Mouse exit
            case SDL_WINDOWEVENT_LEAVE:
//            mMouseFocus = false;
//            updateCaption = true;
            break;

            //Keyboard focus gained
            case SDL_WINDOWEVENT_FOCUS_GAINED:
//            mKeyboardFocus = true;
//            updateCaption = true;
            break;

            //Keyboard focus lost
            case SDL_WINDOWEVENT_FOCUS_LOST:
//            mKeyboardFocus = false;
//            updateCaption = true;
            break;

            //Window minimized
            case SDL_WINDOWEVENT_MINIMIZED:
//            mMinimized = true;
            break;

            //Window maxized
            case SDL_WINDOWEVENT_MAXIMIZED:
//            mMinimized = false;
            break;

            //Window restored
            case SDL_WINDOWEVENT_RESTORED:
//            mMinimized = false;
            break;

            //Hide on close
            case SDL_WINDOWEVENT_CLOSE:
//            SDL_HideWindow( gWindow );
            break;
        }

        //Update window caption with new data
//        if( updateCaption )
        {
//            std::stringstream caption;
//            caption << "SDL Tutorial - ID: " << mWindowID << " MouseFocus:" << ( ( mMouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( mKeyboardFocus ) ? "On" : "Off" );
//            SDL_SetWindowTitle( mWindow, caption.str().c_str() );



            if(e.window.windowID==2)
            {
//                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0xFF, 0x00 );

               //Update Texture
//               gFooTexture.render( ( SCREEN_WIDTH - gFooTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFooTexture.getHeight() ) / 2 );

               //Set rendering space and render to screen
//               SDL_Rect renderQuad = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


               //Set clip rendering dimensions
//               if( clip != NULL )
//               {
//                   renderQuad.w = clip->w;
//                   renderQuad.h = clip->h;
//               }

               SDL_RenderClear( gRenderer );


               SDL_Rect* clip = NULL; double angle = 0.0; SDL_Point* center = NULL; SDL_RendererFlip flip = SDL_FLIP_NONE;
               //Render to screen
               SDL_RenderCopyEx( gRenderer, gFooTexture.mTexture, NULL, NULL, angle, center, flip );

               //Update screen
               SDL_RenderPresent( gRenderer );

            }
            else
            {
//                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0x00 );

                //Update Texture
//                gFooTexture.render( ( SCREEN_WIDTH - gFooTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFooTexture.getHeight() ) / 2 );


                //Set clip rendering dimensions
//                SDL_Rect renderQuad2 = { 0, 0, 100, 100 };
//                if( clip != NULL )
//                {
//                    renderQuad2.w = clip->w;
//                    renderQuad2.h = clip->h;
//                }

                SDL_RenderClear( gRenderer2 );


                SDL_Rect* clip = NULL; double angle = 0.0; SDL_Point* center = NULL; SDL_RendererFlip flip = SDL_FLIP_NONE;
                //Render to screen
                SDL_RenderCopyEx( gRenderer2, gFooTexture.mToolsTexture, NULL, NULL, angle, center, flip );

                //Update screen
                SDL_RenderPresent( gRenderer2 );


            }



        }
    }
}


int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {

        //Load media
        if( !loadMedia()/*0*/ )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    switch(e.type)
                    {
                        case SDL_QUIT :
                        {
                            quit = true;
                            break;
                        }
                        case SDL_MOUSEBUTTONUP:
                        if (e.button.button == SDL_BUTTON_LEFT)
                        {
                            leftMouseButtonDown = false;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN:
                        if (e.button.button == SDL_BUTTON_LEFT)
                        {
                            leftMouseButtonDown = true;
                            break;
                        }
                        case SDL_MOUSEMOTION:
                        if (leftMouseButtonDown)
                        {
                            int mouseX = e.motion.x;
                            int mouseY = e.motion.y;


                            Uint32 drawcolor;
                            Uint8 v = 255 + 255 +255;
                            drawcolor = (0xFF << 24) | (v << 16) | (v << 8) | v;


                            //Texture pixels' modification
                            gFooTexture.lockTexture();
                            Uint32* pixels = (Uint32*)gFooTexture.getPixels();//formattedSurface->pixels;
                            pixels[ (mouseY * SCREEN_WIDTH) + mouseX] = drawcolor;


                            handleEvent(e);
                            gFooTexture.unlockTexture();


                            break;
                        }


                        const int TOTAL_WINDOWS=2;
                        //////////////////////////////////////////////////////////
                        //Handle window events
                       // for( int i = 0; i < TOTAL_WINDOWS; ++i )
                        {
//                            gWindow.handleEvent( e );
//                            toolsWindow.handleEvent( e );


                        }


                        //Update all windows
                        for( int i = 0; i < TOTAL_WINDOWS; ++i )
                        {
//                            gWindow.render();
//                            toolsWindow.render();
//                            gFooTexture.render();

//                            //Clear screen
//                            SDL_RenderClear( gRenderer );
//                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

//                            //Update Texture
//                            gFooTexture.render( ( SCREEN_WIDTH - gFooTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFooTexture.getHeight() ) / 2 );

//                            //Update screen
//                            SDL_RenderPresent( gRenderer );
                        }
                        //////////////////////////////////////////////////////////








                    }

//                    //Update Texture
//                    gFooTexture.render( ( SCREEN_WIDTH - gFooTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFooTexture.getHeight() ) / 2 );

//                    //Update screen
//                    SDL_RenderPresent( gRenderer );
                }

//                Clear screen
//                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

//                SDL_RenderClear( gRenderer );

//                //Render stick figure
//                gFooTexture.render( ( SCREEN_WIDTH - gFooTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFooTexture.getHeight() ) / 2 );

//                //Update screen
//                SDL_RenderPresent( gRenderer );

            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}










































///*This source code copyrighted by Lazy Foo' Productions (2004-2015)
//and may not be redistributed without written permission.*/

////Using SDL, standard IO, strings, and string streams
//#include <SDL.h>
//#include <stdio.h>
//#include <string>
//#include <sstream>

////Screen dimension constants
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

////Total windows
//const int TOTAL_WINDOWS = 3;

//class LWindow
//{
//    public:
//        //Intializes internals
//        LWindow();

//        //Creates window
//        bool init();

//        //Handles window events
//        void handleEvent( SDL_Event& e );

//        //Focuses on window
//        void focus();

//        //Shows windows contents
//        void render();

//        //Deallocates internals
//        void free();

//        //Window dimensions
//        int getWidth();
//        int getHeight();

//        //Window focii
//        bool hasMouseFocus();
//        bool hasKeyboardFocus();
//        bool isMinimized();
//        bool isShown();

//    private:
//        //Window data
//        SDL_Window* mWindow;
//        SDL_Renderer* mRenderer;
//        int mWindowID;

//        //Window dimensions
//        int mWidth;
//        int mHeight;

//        //Window focus
//        bool mMouseFocus;
//        bool mKeyboardFocus;
//        bool mFullScreen;
//        bool mMinimized;
//        bool mShown;
//};

////Starts up SDL and creates window
//bool init();

////Frees media and shuts down SDL
//void close();

////Our custom windows
//LWindow gWindows[ TOTAL_WINDOWS ];

//LWindow::LWindow()
//{
//    //Initialize non-existant window
//    mWindow = NULL;
//    mRenderer = NULL;

//    mMouseFocus = false;
//    mKeyboardFocus = false;
//    mFullScreen = false;
//    mShown = false;
//    mWindowID = -1;

//    mWidth = 0;
//    mHeight = 0;
//}

//bool LWindow::init()
//{
//    //Create window
//    mWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
//    if( mWindow != NULL )
//    {
//        mMouseFocus = true;
//        mKeyboardFocus = true;
//        mWidth = SCREEN_WIDTH;
//        mHeight = SCREEN_HEIGHT;

//        //Create renderer for window
//        mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
//        if( mRenderer == NULL )
//        {
//            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
//            SDL_DestroyWindow( mWindow );
//            mWindow = NULL;
//        }
//        else
//        {
//            //Initialize renderer color
//            SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

//            //Grab window identifier
//            mWindowID = SDL_GetWindowID( mWindow );

//            //Flag as opened
//            mShown = true;
//        }
//    }
//    else
//    {
//        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
//    }

//    return mWindow != NULL && mRenderer != NULL;
//}

//void LWindow::handleEvent( SDL_Event& e )
//{
//    //If an event was detected for this window
//    if( e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID )
//    {
//        //Caption update flag
//        bool updateCaption = false;

//        switch( e.window.event )
//        {
//            //Window appeared
//            case SDL_WINDOWEVENT_SHOWN:
//            mShown = true;
//            break;

//            //Window disappeared
//            case SDL_WINDOWEVENT_HIDDEN:
//            mShown = false;
//            break;

//            //Get new dimensions and repaint
//            case SDL_WINDOWEVENT_SIZE_CHANGED:
//            mWidth = e.window.data1;
//            mHeight = e.window.data2;
//            SDL_RenderPresent( mRenderer );
//            break;

//            //Repaint on expose
//            case SDL_WINDOWEVENT_EXPOSED:
//            SDL_RenderPresent( mRenderer );
//            break;

//            //Mouse enter
//            case SDL_WINDOWEVENT_ENTER:
//            mMouseFocus = true;
//            updateCaption = true;
//            break;

//            //Mouse exit
//            case SDL_WINDOWEVENT_LEAVE:
//            mMouseFocus = false;
//            updateCaption = true;
//            break;

//            //Keyboard focus gained
//            case SDL_WINDOWEVENT_FOCUS_GAINED:
//            mKeyboardFocus = true;
//            updateCaption = true;
//            break;

//            //Keyboard focus lost
//            case SDL_WINDOWEVENT_FOCUS_LOST:
//            mKeyboardFocus = false;
//            updateCaption = true;
//            break;

//            //Window minimized
//            case SDL_WINDOWEVENT_MINIMIZED:
//            mMinimized = true;
//            break;

//            //Window maxized
//            case SDL_WINDOWEVENT_MAXIMIZED:
//            mMinimized = false;
//            break;

//            //Window restored
//            case SDL_WINDOWEVENT_RESTORED:
//            mMinimized = false;
//            break;

//            //Hide on close
//            case SDL_WINDOWEVENT_CLOSE:
//            SDL_HideWindow( mWindow );
//            break;
//        }

//        //Update window caption with new data
//        if( updateCaption )
//        {
//            std::stringstream caption;
//            caption << "SDL Tutorial - ID: " << mWindowID << " MouseFocus:" << ( ( mMouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( mKeyboardFocus ) ? "On" : "Off" );
//            SDL_SetWindowTitle( mWindow, caption.str().c_str() );


//            if(e.window.windowID==2)
//            {
//               SDL_SetRenderDrawColor( mRenderer, 0xFF, 0x00, 0xFF, 0xFF );
//            }
//            else
//            {
//                SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
//            }


//        }
//    }
//}

//void LWindow::focus()
//{
//    //Restore window if needed
//    if( !mShown )
//    {
//        SDL_ShowWindow( mWindow );
//    }

//    //Move window forward
//    SDL_RaiseWindow( mWindow );
//}

//void LWindow::render()
//{
//    if( !mMinimized )
//    {
//        //Clear screen
////        SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
//        SDL_RenderClear( mRenderer );

//        //Update screen
//        SDL_RenderPresent( mRenderer );
//    }
//}

//void LWindow::free()
//{
//    if( mWindow != NULL )
//    {
//        SDL_DestroyWindow( mWindow );
//    }

//    mMouseFocus = false;
//    mKeyboardFocus = false;
//    mWidth = 0;
//    mHeight = 0;
//}

//int LWindow::getWidth()
//{
//    return mWidth;
//}

//int LWindow::getHeight()
//{
//    return mHeight;
//}

//bool LWindow::hasMouseFocus()
//{
//    return mMouseFocus;
//}

//bool LWindow::hasKeyboardFocus()
//{
//    return mKeyboardFocus;
//}

//bool LWindow::isMinimized()
//{
//    return mMinimized;
//}

//bool LWindow::isShown()
//{
//    return mShown;
//}

//bool init()
//{
//    //Initialization flag
//    bool success = true;

//    //Initialize SDL
//    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
//    {
//        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
//        success = false;
//    }
//    else
//    {
//        //Set texture filtering to linear
//        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
//        {
//            printf( "Warning: Linear texture filtering not enabled!" );
//        }

//        //Create window
//        if( !gWindows[ 0 ].init() )
//        {
//            printf( "Window 0 could not be created!\n" );
//            success = false;
//        }
//    }

//    return success;
//}

//void close()
//{
//    //Destroy windows
//    for( int i = 0; i < TOTAL_WINDOWS; ++i )
//    {
//        gWindows[ i ].free();
//    }

//    //Quit SDL subsystems
//    SDL_Quit();
//}

//int main( int argc, char* args[] )
//{
//    //Start up SDL and create window
//    if( !init() )
//    {
//        printf( "Failed to initialize!\n" );
//    }
//    else
//    {
//        //Initialize the rest of the windows
//        for( int i = 1; i < TOTAL_WINDOWS; ++i )
//        {
//            gWindows[ i ].init();
//        }

//        //Main loop flag
//        bool quit = false;

//        //Event handler
//        SDL_Event e;

//        //While application is running
//        while( !quit )
//        {
//            //Handle events on queue
//            while( SDL_PollEvent( &e ) != 0 )
//            {
//                //User requests quit
//                if( e.type == SDL_QUIT )
//                {
//                    quit = true;
//                }

//                //Handle window events
//                for( int i = 0; i < TOTAL_WINDOWS; ++i )
//                {
//                    gWindows[ i ].handleEvent( e );
//                }

//                //Pull up window
//                if( e.type == SDL_KEYDOWN )
//                {
//                    switch( e.key.keysym.sym )
//                    {
//                        case SDLK_1:
//                        gWindows[ 0 ].focus();
//                        break;

//                        case SDLK_2:
//                        gWindows[ 1 ].focus();
//                        break;

//                        case SDLK_3:
//                        gWindows[ 2 ].focus();
//                        break;
//                    }
//                }
//            }

//            //Update all windows
//            for( int i = 0; i < TOTAL_WINDOWS; ++i )
//            {
//                gWindows[ i ].render();
//            }

//            //Check all windows
//            bool allWindowsClosed = true;
//            for( int i = 0; i < TOTAL_WINDOWS; ++i )
//            {
//                if( gWindows[ i ].isShown() )
//                {
//                    allWindowsClosed = false;
//                    break;
//                }
//            }

//            //Application closed all windows
//            if( allWindowsClosed )
//            {
//                quit = true;
//            }
//        }
//    }

//    //Free resources and close SDL
//    close();

//    return 0;
//}
