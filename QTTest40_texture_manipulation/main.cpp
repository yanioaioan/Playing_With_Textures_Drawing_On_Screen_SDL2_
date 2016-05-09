//#include <SDL.h>

//#include <SDL_image.h>
//#include <iostream>

//int main(int argc, char ** argv)

//{

//    bool quit = false;

//    SDL_Event event;

//    SDL_Init(SDL_INIT_VIDEO);

//    IMG_Init(IMG_INIT_JPG);

//    SDL_Window * drawingWindow = SDL_CreateWindow("SDL2 Grayscale",

//        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mainwindowWidth, mainwindowHeight, 0);

//    SDL_Renderer * mainwindowRenderer = SDL_CreateRenderer(drawingWindow, -1, 0);

//    SDL_Surface * image = IMG_Load("antipaxoi.png");
//    image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);
//    Uint32 * pixels = (Uint32 *)image->pixels;


////    SDL_Texture * mainwindowTexture = SDL_CreateTextureFromSurface(mainwindowRenderer,image);
//    SDL_Texture * mainwindowTexture = SDL_CreateTexture(mainwindowRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, image->w, image->h);


//    while (!quit)
//    {
//        SDL_UpdateTexture(mainwindowTexture, NULL, image->pixels, image->w * sizeof(Uint32));

//        SDL_WaitEvent(&event);

//        switch (event.type)
//        {

//            case SDL_QUIT:

//                quit = true;

//                break;
//            case SDL_KEYDOWN:

//                switch (event.key.keysym.sym)

//                {

//                    case SDLK_g:

//                        for (int y = 0; y < image->h; y++)

//                        {

//                            for (int x = 0; x < image->w; x++)

//                            {

//                                Uint32 pixel = pixels[y * image->w + x];

//                                // TODO convert pixel to grayscale here

//                                //get this pixel's r,g,b colors
//                                Uint8 r = pixel >> 16 & 0xFF;
//                                Uint8 g = pixel >> 8 & 0xFF;
//                                Uint8 b = pixel & 0xFF;

//                                //manipulate colors and save them back to v
//                                //Uint8 v = 0.212671f * r + 0.715160f * g + 0.072169f * b;
////                                r=255;g=0;b=0;
////


////                                std::cout<<(int)r<<","<<(int)g<<","<<(int)b<<std::endl;

//                                r=255;g=255;b=0;



//                                //assign v to pixels
//                                pixel = (0xFF << 24) | (r << 16) | (g << 8) | b;

//                                pixels[y * image->w + x] = pixel;


//                            }

//                        }

//                break;

//                }

//            break;

//        }

//        SDL_RenderCopy(mainwindowRenderer, mainwindowTexture, NULL, NULL);

//        SDL_RenderPresent(mainwindowRenderer);

//    }

//    SDL_DestroyTexture(mainwindowTexture);

//    SDL_FreeSurface(image);

//    SDL_DestroyRenderer(mainwindowRenderer);

//    SDL_DestroyWindow(drawingWindow);

//    IMG_Quit();

//    SDL_Quit();

//    return 0;

//}

















///*This source code copyrighted by Lazy Foo' Productions (2004-2015)
//and may not be redistributed without written permission.*/

////Using SDL, SDL_image, standard IO, and strings
//#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>

//#include <iostream>
#include <cstring>


////Screen dimension constants
//const int SCREEN_WIDTH = 720;
//const int SCREEN_HEIGHT = 576;
//TTF_Font *gFont;
////typedef enum {FALSE,TRUE} boolean;

//bool leftMouseButtonDown=false;
//const int WHITE=255;
//int windowId=-1;

//void handleEvent( SDL_Event& e );

////Texture wrapper class
//class LTexture
//{
//    public:
//        //Initializes variables
//        LTexture();

//        //Deallocates memory
//        ~LTexture();

//        //Loads image at specified toolPath
//        bool loadFromFile( std::string toolPath );

//        //Loads mainwindowTexture
//        bool loadTexture();

//        #ifdef _SDL_TTF_H
//        //Creates image from font string
//        bool loadFromRenderedText(std::string textureText, SDL_Color textColor , int x, int y);
//        #endif

//        //Deallocates mainwindowTexture
//        void free();

//        //Set color modulation
//        void setColor( Uint8 red, Uint8 green, Uint8 blue );

//        //Set blending
//        void setBlendMode( SDL_BlendMode blending );

//        //Set alpha modulation
//        void setAlpha( Uint8 alpha );

//        //Renders mainwindowTexture at given point
//        void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

//        void update( );

//        //Gets image dimensions
//        int getWidth();
//        int getHeight();

//        //Pixel manipulators
//        bool lockTexture();
//        bool unlockTexture();
//        void* getPixels();
//        void* getToolsPixels();

//        int getPitch();

//        //The actual hardware mainwindowTexture
//        SDL_Texture* mTexture;
//        SDL_Texture* mToolsTexture;

//    private:

//        void* mPixels;
//        void* mToolsPixels;
//        int mPitch;
//        int mToolsPitch;


//        //Image dimensions
//        int mWidth;
//        int mHeight;
//};

////Starts up SDL and creates drawingWindow
//bool init();

////Loads media
//bool loadMedia();

////Frees media and shuts down SDL
//void close();

////The drawingWindow we'll be rendering to
//SDL_Window* gWindow = NULL;
//SDL_Window* toolsWindow = NULL;

////The drawingWindow mainwindowRenderer
//SDL_Renderer* gRenderer = NULL;
//SDL_Renderer* gtoolsRenderer = NULL;


////Scene textures
//LTexture gFooTexture;
//SDL_Surface* toolsFormattedSurface;
//SDL_Surface* gScreenSurface;
//LTexture::LTexture()
//{
//    //Initialize
//    mTexture = NULL;
//    mWidth = 0;
//    mHeight = 0;
//    mPixels = NULL;
//    mToolsPixels = NULL;
//    mPitch = 0;
//    mToolsPitch = 0;
//}

//LTexture::~LTexture()
//{
//    //Deallocate
//    free();
//}
//bool LTexture::loadFromFile( std::string toolPath )
//{
//    //Get rid of preexisting mainwindowTexture
//    free();

//    //The final mainwindowTexture
//    SDL_Texture* newTexture = NULL;

////    //Load image at specified toolPath
////    SDL_Surface* toolsSurface = IMG_Load( toolPath.c_str() );
////    if( toolsSurface == NULL )
////    {
////        printf( "Unable to load image %s! SDL_image Error: %s\n", toolPath.c_str(), IMG_GetError() );
////    }
////    else
////    {
//        //Convert surface to display format

////        toolsFormattedSurface = SDL_ConvertSurface( toolsSurface,  SDL_GetWindowSurface(gWindow)->format, NULL );
////        toolsFormattedSurface = SDL_ConvertSurfaceFormat( toolsSurface, SDL_PIXELFORMAT_ARGB8888, NULL );

////        if( toolsFormattedSurface == NULL )
////        {
////            printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
////        }
////        else
//        {


//            //Create blank streamable mainwindowTexture
//            newTexture = SDL_CreateTexture( gRenderer,SDL_GetWindowPixelFormat( gWindow ), SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT );
//            if( newTexture == NULL )
//            {
//                printf( "Unable to create blank mainwindowTexture! SDL Error: %s\n", SDL_GetError() );
//            }
//            else
//            {
//                //Lock mainwindowTexture for manipulation
//                SDL_LockTexture( newTexture, NULL, &mPixels, &mPitch );

////                //Copy loaded/formatted surface pixels
////                memcpy( mPixels, toolsFormattedSurface->pixels, toolsFormattedSurface->pitch * toolsFormattedSurface->h );



////                //Unlock mainwindowTexture to update
//                SDL_UnlockTexture( newTexture );
//                mPixels = NULL;

//                //Get image dimensions
//                mWidth = /*toolsFormattedSurface->w*/ SCREEN_WIDTH;
//                mHeight = /*toolsFormattedSurface->h*/ SCREEN_HEIGHT;
//            }

////            //Get rid of old formatted surface
////            SDL_FreeSurface( toolsFormattedSurface );
//        }

//        //Get rid of old loaded surface
////        SDL_FreeSurface( toolsSurface );
////    }

//    //Return success
//    mTexture = newTexture;
//    return mTexture != NULL;
//}



//bool LTexture::loadTexture()
//{
//    //Get rid of preexisting mainwindowTexture
//    free();

//    //The final mainwindowTexture
//    SDL_Texture* newTexture = NULL;
//    SDL_Texture* toolsTexture = NULL;

//        {
//            //Create blank streamable mainwindowTexture
//            newTexture = SDL_CreateTexture( gRenderer,SDL_GetWindowPixelFormat( gWindow ), SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT );
//            toolsTexture = SDL_CreateTexture( gtoolsRenderer,SDL_GetWindowPixelFormat( toolsWindow ), SDL_TEXTUREACCESS_STREAMING, 200, 200 );

//            if( newTexture == NULL || toolsTexture == NULL)
//            {
//                printf( "Unable to create blank mainwindowTexture! SDL Error: %s\n", SDL_GetError() );
//            }
//            else
//            {
//                //Lock mainwindowTexture for manipulation
//                SDL_LockTexture( newTexture, NULL, &mPixels, &mPitch );
//                SDL_LockTexture( toolsTexture, NULL, &mToolsPixels, &mToolsPitch );

////                //Copy loaded/formatted surface pixels
////                memcpy( mPixels, toolsFormattedSurface->pixels, toolsFormattedSurface->pitch * toolsFormattedSurface->h );

//                //set backgrounf to white
////                memset(mPixels, WHITE , SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

////                memset(mToolsPixels, 0 , 100 * 100 * sizeof(Uint32));



//                //Unlock mainwindowTexture to update
//                SDL_UnlockTexture( newTexture );
//                mPixels = NULL;
//                SDL_UnlockTexture( toolsTexture );
//                mToolsPixels = NULL;

//                //Get image dimensions
//                mWidth =  SCREEN_WIDTH;
//                mHeight = SCREEN_HEIGHT;
//            }

//        }



//    //Return success
//    mTexture = newTexture;
//    mToolsTexture = toolsTexture;
//    return mTexture != NULL && mToolsTexture !=NULL;
//}



//#ifdef _SDL_TTF_H
//bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor,int x, int y )
//{

//    /*Create 100 surfaces blit one to the existing one*/

//    //Get rid of preexisting mainwindowTexture
////    free();

//     gFont = TTF_OpenFont("arial.ttf", 10);
//    //Render text surface

//     SDL_Surface* textSurface;
////     for(int i=0;i<100;i++)
//     {
//     textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
////    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(gFont, textureText.c_str(), textColor ,300);

//        SDL_Rect textLocation = { x, y, 8, 10 };
//    //SDL_BlitSurface(textSurface, NULL, toolsFormattedSurface, &textLocation);





//    //Then create a mainwindowTexture from the "final textSurface"

//    if( textSurface != NULL )
//    {
//        //Create mainwindowTexture from surface pixels
//        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
//        if( mTexture == NULL )
//        {
//            printf( "Unable to create mainwindowTexture from rendered text! SDL Error: %s\n", SDL_GetError() );
//        }
//        else
//        {
//            //Get image dimensions
//            mWidth = textSurface->w;
//            mHeight = textSurface->h;


//            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

//            //do not clear the screen
////            SDL_RenderClear( gRenderer );

//            SDL_SetTextureColorMod(mTexture,textColor.r,textColor.g,textColor.b);
//            SDL_RenderCopy(gRenderer,mTexture, NULL, /*&charLocation*/  &textLocation);



//        }


//    }
//    else
//    {
//        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
//    }



//     }
//    TTF_CloseFont(gFont);
//    //Get rid of old surface
//    SDL_FreeSurface( textSurface );

//    //Return success
//    return mTexture != NULL;
//}
//#endif

//void LTexture::free()
//{
//    //Free mainwindowTexture if it exists
//    if( mTexture != NULL )
//    {
//        SDL_DestroyTexture( mTexture );
//        SDL_DestroyTexture( mToolsTexture );
//        mTexture = NULL;
//        mToolsTexture = NULL;
//        mWidth = 0;
//        mHeight = 0;
//        mPixels = NULL;
//        mPitch = 0;

//        mToolsPixels = NULL;
//        mToolsPitch = 0;
//    }
//}

//void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
//{
//    //Modulate mainwindowTexture rgb
//    SDL_SetTextureColorMod( mTexture, red, green, blue );
//}

//void LTexture::setBlendMode( SDL_BlendMode blending )
//{
//    //Set blending function
//    SDL_SetTextureBlendMode( mTexture, blending );
//}

//void LTexture::setAlpha( Uint8 alpha )
//{
//    //Modulate mainwindowTexture alpha
//    SDL_SetTextureAlphaMod( mTexture, alpha );
//}

////void LTexture::update()
////{
////    SDL_UpdateTexture((SDL_Texture*)this, NULL, toolsFormattedSurface->pixels, toolsFormattedSurface->pitch);
////}

//void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
//{
////    //Set rendering space and render to screen
////    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
////    SDL_Rect renderQuad2 = { 0, 0, 100, 100 };

////    //Set clip rendering dimensions
////    if( clip != NULL )
////    {
////        renderQuad.w = clip->w;
////        renderQuad.h = clip->h;
////    }

////    //Render to screen
////    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );

////    if( clip != NULL )
////    {
////        renderQuad2.w = clip->w;
////        renderQuad2.h = clip->h;
////    }

////    SDL_RenderCopyEx( gRenderer, mToolsTexture, clip, &renderQuad2, angle, center, flip );

//}

//int LTexture::getWidth()
//{
//    return mWidth;
//}

//int LTexture::getHeight()
//{
//    return mHeight;
//}

//bool LTexture::lockTexture()
//{
//    bool success = true;

//    //Texture is already locked
//    if( mPixels != NULL || mToolsPixels !=NULL)
//    {
//        printf( "Texture is already locked!\n" );
//        success = false;
//    }
//    //Lock mainwindowTexture
//    else
//    {
//        if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 )
//        {
//            printf( "Unable to lock mainwindowTexture! %s\n", SDL_GetError() );
//            success = false;
//        }

//        if( SDL_LockTexture( mToolsTexture, NULL, &mToolsPixels, &mToolsPitch ) != 0 )
//        {
//            printf( "Unable to lock mainwindowTexture! %s\n", SDL_GetError() );
//            success = false;
//        }
//    }

//    return success;
//}

//bool LTexture::unlockTexture()
//{
//    bool success = true;

//    //Texture is not locked
//    if( mPixels == NULL || mToolsPixels == NULL )
//    {
//        printf( "Texture is not locked!\n" );
//        success = false;
//    }
//    //Unlock mainwindowTexture
//    else
//    {
//        SDL_UnlockTexture( mTexture );
//        mPixels = NULL;
//        mPitch = 0;

//        SDL_UnlockTexture( mToolsTexture );
//        mToolsPixels = NULL;
//        mToolsPitch = 0;
//    }

//    return success;
//}

//void* LTexture::getPixels()
//{
//    return mPixels;
//}

//void* LTexture::getToolsPixels()
//{
//    return mToolsPixels;
//}

//int LTexture::getPitch()
//{
//    return mPitch;
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
//        //Set mainwindowTexture filtering to linear
//        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
//        {
//            printf( "Warning: Linear mainwindowTexture filtering not enabled!" );
//        }

//        //Create drawingWindow
//        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
//        //Grab drawingWindow identifier
//        windowId = SDL_GetWindowID( gWindow );

//        toolsWindow = SDL_CreateWindow( "Tool Box", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, 0 );
//        windowId = SDL_GetWindowID( toolsWindow );


//        if( gWindow == NULL || toolsWindow ==NULL)
//        {
//            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
//            success = false;
//        }
//        else
//        {

//            //Create mainwindowRenderer for drawingWindow
//            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
//            gtoolsRenderer = SDL_CreateRenderer( toolsWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
////            gRendererTools = SDL_CreateRenderer( toolsWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
//            if( gRenderer == NULL  )
//            {
//                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
//                success = false;
//            }
//            else
//            {
//                //Initialize mainwindowRenderer color
//                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
////                SDL_SetRenderDrawColor( gRendererTools, 0xFF, 0x00, 0x00, 0xFF );

//                //Initialize PNG loading
//                int imgFlags = IMG_INIT_PNG;
//                if( !( IMG_Init( imgFlags ) & imgFlags ) )
//                {
//                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
//                    success = false;
//                }


//                //Initialize SDL_ttf
//                if( TTF_Init() == -1 )
//                { return false; }



//            }
//        }
//    }

//    return success;
//}

//Uint32 getpixel(SDL_Surface *surface, int x, int y)
//{
//    int bpp = surface->format->BytesPerPixel;
//    /* Here p is the address to the pixel we want to retrieve */
//    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

//    switch(bpp) {
//    case 1:
//        return *p;

//    case 2:
//        return *(Uint16 *)p;

//    case 3:
//        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
//            return p[0] << 16 | p[1] << 8 | p[2];
//        else
//            return p[0] | p[1] << 8 | p[2] << 16;

//    case 4:
//        return *(Uint32 *)p;

//    default:
//        return 0;       /* shouldn't happen, but avoids warnings */
//    }
//}

//int powerof(int x,int y)
//{
//    int tmp=x;
//    for(int i=1;i<y;i++)
//    {

//        tmp*=x;
//    }
//    return tmp;
//}


//std::string getGrayShade(int avRGBVal)
//{
//    std::string asciichar = " ";


//    if (avRGBVal >= 225)
//    {
//        asciichar = "`";
//    }
//    else if (avRGBVal >= 200)
//    {
//        asciichar = ".";
//    }
//    else if (avRGBVal >= 175)
//    {
//        asciichar = ":";
//    }
//    else if (avRGBVal >= 150)
//    {
//        asciichar = "!";
//    }
//    else if (avRGBVal >= 125)
//    {
//        asciichar = "o";
//    }

//    else if (avRGBVal >= 100)
//    {
//        asciichar = "*";
//    }
//    else if (avRGBVal >= 75)
//    {
//        asciichar = "8";
//    }
//    else if (avRGBVal >= 50)
//    {
//        asciichar = "%";
//    }
//    else if (avRGBVal >= 25)
//    {
//        asciichar = "#";
//    }
//    else
//    {
//        asciichar = "@";
//    }

//    return asciichar;
//}


//bool loadMedia()
//{
//    //Loading success flag
//    bool success = true;


//    //Load foo' mainwindowTexture
////    if( !gFooTexture.loadFromFile( "lion.png" ) )
//    if(!gFooTexture.loadTexture())
//    {
//        printf( "Failed to load corner mainwindowTexture!\n" );
//        success = false;
//    }
//    else
//    {
//        //Lock mainwindowTexture
////        if( !gFooTexture.lockTexture() )
////        {
////            printf( "Unable to lock Foo' mainwindowTexture!\n" );
////        }
//        //Manual color key
////        else
////        {
//            //Get pixel data
////            Uint32* pixels = (Uint32*)gFooTexture.getPixels();//toolsFormattedSurface->pixels;
////            int pixelCount = ( gFooTexture.getPitch() / 4 ) * gFooTexture.getHeight();


//            //Map colors
////            Uint32 colorKey = SDL_MapRGB( SDL_GetWindowSurface( gWindow )->format, 0, 0xFF, 0xFF );
////            Uint32 transparent = SDL_MapRGBA( SDL_GetWindowSurface( gWindow )->format, 0xFF, 0xFF, 0xFF, 0x00 );

////            Uint32 colorKey = SDL_MapRGB( toolsFormattedSurface->format, 0, 0xFF, 0xFF );
////            Uint32 transparent = SDL_MapRGBA( toolsFormattedSurface->format, 0XFF, 0XFF, 0XFF, 0xFF );

////                        for( int i = 0; i < pixelCount; ++i )
////                        {
////                            if( pixels[ i ] == colorKey )
////                            {
////                                pixels[ i ] = transparent;
////                            }
////                        }



//            //Averagine by block
//            //Color key pixels
//            //int powerof2=powerof(2,10);//for a toolsFormattedSurface->w/64 block pixel width this should produce 8 blocks of 8 pixels
////            int blockDivider=64;
////            int block_width=toolsFormattedSurface->w/blockDivider;
////            int block_height=toolsFormattedSurface->h/blockDivider;

////            std::string blockCharacterString;
////            //For each block every block_width pixels
////            for(int bx = block_width; bx <= toolsFormattedSurface->w;  bx += block_width)
////            {
////                //For each block every block_height pixels
////                for(int by = block_height; by <= toolsFormattedSurface->h; by += block_height)
////                {

////                    //total sum of Red,Green,Blue channel values
////                    float sumR=0;
////                    float sumG=0;
////                    float sumB=0;

////                    //CurrentPixel
////                    Uint32 pixel;

////                    int blockPixelcounter=0;
////                    //For each block every block_height pixels
////                    for(int x = bx-block_width; x < bx; x++)
////                    {
////                        for(int y = by-block_height; y < by; y++)
////                        {

////                            Uint8 red ;
////                            Uint8 green ;
////                            Uint8 blue ;
////                            pixel=pixels[x + y * toolsFormattedSurface->w];

////                            SDL_GetRGB( pixel, toolsFormattedSurface->format ,  &red, &green, &blue );


////                            sumR=sumR+red;
////                            sumG=sumG+green;
////                            sumB= sumB+blue;
////                            blockPixelcounter++;


////                        }

////                    }//square block end


////                    //get the average chanel color
////                    int avR=sumR/blockPixelcounter; int avG=sumG/blockPixelcounter; int avB=sumB/blockPixelcounter;

////                    //Gray Scale it - based on each rgb value
//////                    Uint8 v = 0.212671f * red  + 0.715160f * green  + 0.072169f * blue;

////                    //Gray Scale it - based on the average rgb value
////                    Uint8 v = 0.212671f * avR  + 0.715160f * avG  + 0.072169f * avB;
////                    //pixel = (0xFF << 24) | (v << 16) | (v << 8) | v;



//                    /*
//                     * instead of modifying pixel in the line above,
//                      we can query the character which is going to replace this block based
//                      on the average grayscale value of the 3 R,G,B channels
//                     */
////                    int avRGBValue=v /*  OR (avR+avG+avB)/3  */;
////                    blockCharacterString+=getGrayShade(avRGBValue);




////                    //iterate and replace all pixel color values with this average grayscal value
////                    for(size_t x = bx-block_width; x < bx; x++)
////                    {
////                        for(size_t y = by-block_height; y < by; y++)
////                        {
////                            //manually change the color of the pixel
////                                    pixel = (0xFF << 24) | (red << 16) | (green << 8) | blue;
////                            pixels [(toolsFormattedSurface->w* y)+x ] = pixel;
////                        }

////                    }//square block end replacing values



////                            //Avegage Block Color
////                            sumR+=red; sumG+=green; sumB+=blue;
////                            pixels [(gFooTexture.getWidth()* by)+bx ] = 255;


//                    //Create a mainwindowTexture (appropriate chosen character, appropriately colored) for each block of pixels at bx,by to be replaced
////                    SDL_Color AV_BLOCK_COLOR = {avR,avG,avB};

//                    /*
//                     * and now we can create a mainwindowTexture of the characters in the blockCharacterString
//                     */
////                    gFooTexture.loadFromRenderedText(getGrayShade(avRGBValue),AV_BLOCK_COLOR,bx,by);

////                }

//                //when we reach the end of each row of pixels we add a new line \n
//                //blockCharacterString+="\n";


//            }

//            //At the end. Get pixels of the surface associated with the gRenderer (toolsFormattedSurface)
//            //save the image
////            Uint32 * finaltexturePixels = (Uint32 *)toolsFormattedSurface->pixels;
////            SDL_RenderReadPixels(gRenderer, &toolsFormattedSurface->clip_rect, toolsFormattedSurface->format->format, finaltexturePixels, toolsFormattedSurface->w * toolsFormattedSurface->format->BytesPerPixel);
////            SDL_Surface* saveSurface = SDL_CreateRGBSurfaceFrom(finaltexturePixels, toolsFormattedSurface->w, toolsFormattedSurface->h,
////                                                                toolsFormattedSurface->format->BitsPerPixel,
////                                                                toolsFormattedSurface->w * toolsFormattedSurface->format->BytesPerPixel,
////                                                                toolsFormattedSurface->format->Rmask, toolsFormattedSurface->format->Gmask,
////                                                                toolsFormattedSurface->format->Bmask, toolsFormattedSurface->format->Amask);


////            SDL_SaveBMP(saveSurface, "MYASCIICOLOREDIMAGE.bmp");


//            //Get rid of old formatted surface
////            SDL_FreeSurface( toolsFormattedSurface );

//            //Unlock mainwindowTexture
////            gFooTexture.unlockTexture();
////        }
////    }

//    return success;
//}

//void close()
//{
//    //Free loaded images
//    gFooTexture.free();

//    //Destroy drawingWindow
//    SDL_DestroyRenderer( gRenderer );
//    SDL_DestroyWindow( gWindow );
//    gWindow = NULL;
//    gRenderer = NULL;

//    SDL_DestroyRenderer( gtoolsRenderer );
//    SDL_DestroyWindow( toolsWindow );
//    toolsWindow = NULL;
//    gtoolsRenderer = NULL;


//    //Quit SDL_ttf
//    TTF_Quit();

//    //Quit SDL subsystems
//    IMG_Quit();
//    SDL_Quit();
//}


//void handleEvent( SDL_Event& e )
//{
//    //If an event was detected for this drawingWindow
////    if( e.type == SDL_WINDOWEVENT && e.drawingWindow.windowID == 2 )
//    {
//        //Caption update flag
////        bool updateCaption = false;

//        switch( e.drawingWindow.event )
//        {
//            //Window appeared
//            case SDL_WINDOWEVENT_SHOWN:
////            mShown = true;
//            break;

//            //Window disappeared
//            case SDL_WINDOWEVENT_HIDDEN:
////            mShown = false;
//            break;

//            //Get new dimensions and repaint
//            case SDL_WINDOWEVENT_SIZE_CHANGED:
////            mWidth = e.drawingWindow.data1;
////            mHeight = e.drawingWindow.data2;
////            SDL_RenderPresent( gRenderer );
////            SDL_RenderPresent( gtoolsRenderer );
//            break;

//            //Repaint on expose
//            case SDL_WINDOWEVENT_EXPOSED:
////            SDL_RenderPresent( gRenderer );
////            SDL_RenderPresent( gtoolsRenderer );
//            break;

//            //Mouse enter
//            case SDL_WINDOWEVENT_ENTER:
////            mMouseFocus = true;
////            updateCaption = true;
//            break;

//            //Mouse exit
//            case SDL_WINDOWEVENT_LEAVE:
////            mMouseFocus = false;
////            updateCaption = true;
//            break;

//            //Keyboard focus gained
//            case SDL_WINDOWEVENT_FOCUS_GAINED:
////            mKeyboardFocus = true;
////            updateCaption = true;
//            break;

//            //Keyboard focus lost
//            case SDL_WINDOWEVENT_FOCUS_LOST:
////            mKeyboardFocus = false;
////            updateCaption = true;
//            break;

//            //Window minimized
//            case SDL_WINDOWEVENT_MINIMIZED:
////            mMinimized = true;
//            break;

//            //Window maxized
//            case SDL_WINDOWEVENT_MAXIMIZED:
////            mMinimized = false;
//            break;

//            //Window restored
//            case SDL_WINDOWEVENT_RESTORED:
////            mMinimized = false;
//            break;

//            //Hide on close
//            case SDL_WINDOWEVENT_CLOSE:
////            SDL_HideWindow( gWindow );
//            break;
//        }

//        //Update drawingWindow caption with new data
////        if( updateCaption )
//        {
////            std::stringstream caption;
////            caption << "SDL Tutorial - ID: " << mWindowID << " MouseFocus:" << ( ( mMouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( mKeyboardFocus ) ? "On" : "Off" );
////            SDL_SetWindowTitle( mWindow, caption.str().c_str() );



//            if(e.drawingWindow.windowID==2)
//            {
////                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0xFF, 0x00 );

//               //Update Texture
////               gFooTexture.render( ( SCREEN_WIDTH - gFooTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFooTexture.getHeight() ) / 2 );

//               //Set rendering space and render to screen
////               SDL_Rect renderQuad = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


//               //Set clip rendering dimensions
////               if( clip != NULL )
////               {
////                   renderQuad.w = clip->w;
////                   renderQuad.h = clip->h;
////               }




////               SDL_RenderClear( gRenderer );


//               SDL_Rect* clip = NULL; double angle = 0.0; SDL_Point* center = NULL; SDL_RendererFlip flip = SDL_FLIP_NONE;
//               //Render to screen
//               SDL_RenderCopy/*Ex*/( gRenderer, gFooTexture.mTexture, NULL, NULL/*, angle, center, flip*/ );

//               //Update screen
//               SDL_RenderPresent( gRenderer );

//            }
//            else
//            {
////                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0x00 );

//                //Update Texture
////                gFooTexture.render( ( SCREEN_WIDTH - gFooTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFooTexture.getHeight() ) / 2 );


//                //Set clip rendering dimensions
////                SDL_Rect renderQuad2 = { 0, 0, 100, 100 };
////                if( clip != NULL )
////                {
////                    renderQuad2.w = clip->w;
////                    renderQuad2.h = clip->h;
////                }

////                SDL_RenderClear( gtoolsRenderer );


//                SDL_Rect* clip = NULL; double angle = 0.0; SDL_Point* center = NULL; SDL_RendererFlip flip = SDL_FLIP_NONE;
//                //Render to screen
//                SDL_RenderCopy( gtoolsRenderer, gFooTexture.mToolsTexture, NULL, NULL/*, angle, center, flip*/ );

//                //Update screen
//                SDL_RenderPresent( gtoolsRenderer );


//            }



//        }
//    }
//}


//int main( int argc, char* args[] )
//{
//    //Start up SDL and create drawingWindow
//    if( !init() )
//    {
//        printf( "Failed to initialize!\n" );
//    }
//    else
//    {

//        //Load media
//        if( !loadMedia()/*0*/ )
//        {
//            printf( "Failed to load media!\n" );
//        }
//        else
//        {
//            //Main loop flag
//            bool quit = false;

//            gFooTexture.lockTexture();
//            Uint32* pixels = (Uint32*)gFooTexture.getPixels();//toolsFormattedSurface->pixels;
//            Uint32* toolspixels = (Uint32*)gFooTexture.getToolsPixels();//toolsFormattedSurface->pixels;

//            //Event handler
//            SDL_Event e;

//            //While application is running
//            while( !quit )
//            {

//                //Handle events on queue
//                while( SDL_PollEvent( &e ) != 0 )
//                {

//                    //User requests quit
//                    switch(e.type)
//                    {
//                        case SDL_QUIT :
//                        {
//                            quit = true;
//                            break;
//                        }
//                        case SDL_MOUSEBUTTONUP:
//                        if (e.button.button == SDL_BUTTON_LEFT)
//                        {
//                            leftMouseButtonDown = false;
//                            break;
//                        }
//                        case SDL_MOUSEBUTTONDOWN:
//                        if (e.button.button == SDL_BUTTON_LEFT)
//                        {
//                            leftMouseButtonDown = true;
//                        }
//                        case SDL_MOUSEMOTION:
//                        if (leftMouseButtonDown)
//                        {
//                            int mouseX = e.motion.x;
//                            int mouseY = e.motion.y;


//                            Uint32 drawcolor;
//                            Uint8 v = 255 + 255 +255;
//                            drawcolor = (0xFF << 24) | (v << 16) | (v << 8) | v;


//                            std::cout<<"e.drawingWindow.windowID="<<e.drawingWindow.windowID<<std::endl;
//                            //Texture pixels' modification
//                            if (e.drawingWindow.windowID==2)
//                            {

//                                pixels[ (mouseY * SCREEN_WIDTH) + mouseX] = drawcolor;

//                            }

//                            if (e.drawingWindow.windowID==3)
//                            {

//                                toolspixels[ (mouseY * 200) + mouseX] = drawcolor;

//                            }

//                            break;





//                        }
//                        handleEvent(e);



//                        const int TOTAL_WINDOWS=2;
//                        //////////////////////////////////////////////////////////
//                        //Handle drawingWindow events
//                       // for( int i = 0; i < TOTAL_WINDOWS; ++i )
//                        {
////                            gWindow.handleEvent( e );
////                            toolsWindow.handleEvent( e );


//                        }


//                        //Update all windows
//                        for( int i = 0; i < TOTAL_WINDOWS; ++i )
//                        {
////                            gWindow.render();
////                            toolsWindow.render();
////                            gFooTexture.render();

////                            //Clear screen
////                            SDL_RenderClear( gRenderer );
////                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

////                            //Update Texture
////                            gFooTexture.render( ( SCREEN_WIDTH - gFooTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFooTexture.getHeight() ) / 2 );

////                            //Update screen
////                            SDL_RenderPresent( gRenderer );
//                        }
//                        //////////////////////////////////////////////////////////








//                    }

////                    //Update Texture
////                    gFooTexture.render( ( SCREEN_WIDTH - gFooTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFooTexture.getHeight() ) / 2 );

////                    //Update screen
////                    SDL_RenderPresent( gRenderer );
//                }


//                 gFooTexture.unlockTexture();


////                Clear screen
////                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

////                SDL_RenderClear( gRenderer );

////                //Render stick figure
////                gFooTexture.render( ( SCREEN_WIDTH - gFooTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFooTexture.getHeight() ) / 2 );

////                //Update screen
////                SDL_RenderPresent( gRenderer );

//            }
//        }
//    }

//    //Free resources and close SDL
//    close();

//    return 0;
//}





















#include <iostream>
#include <SDL.h>
#include <math.h>

bool leftMouseButtonDown = false;
bool quit = false;
SDL_Event event;


SDL_Window * drawingWindow;
int drawingWindowId;
int ToolsWindowId;

SDL_Renderer * mainwindowRenderer;
SDL_Texture * mainwindowTexture;

SDL_Renderer * toolsRenderer;
SDL_Texture * toolsTexture;


int mainwindowWidth =640;
int mainwindowHeight =480;
int toolswindowWidth =100;

Uint32 * mainwindowPixels = new Uint32[mainwindowWidth * mainwindowHeight];
void * toolsPixels = new Uint32[mainwindowWidth * mainwindowHeight];
//Uint32 *backbufferPixels = new Uint32[mainwindowWidth * mainwindowHeight];
Uint32 * backbufferPixels=NULL;// (Uint32*)malloc(mainwindowWidth * mainwindowHeight * sizeof(Uint32));
int sizeofbackbufferPixels;

Uint8 tmpColor;


//ToolBox Booleans
typedef enum {FALSE,TRUE} boolean;
boolean drawRectangle =FALSE;
boolean drawPointLine =FALSE;
boolean drawPointCircle =FALSE;
boolean drawPointPencil =FALSE;
boolean drawPointBrush =FALSE;
boolean drawPointBucketFill =FALSE;
boolean drawPointRedColor =FALSE;
boolean drawPointBlackColor =FALSE;
boolean drawPointEraser =FALSE;

boolean NOWDRAWING =FALSE;

SDL_Color colorpicked;

///////////////////////////////////////////////////////////////////
/// \brief toolsSurface
const char * toolPath="toolbox.png";
SDL_Surface* toolsSurface;
SDL_Surface * mainwindowSurface;

SDL_Surface* toolsFormattedSurface;
SDL_Surface* mainwindowFormattedSurface;



// Main Mid-Point Circle Algorithm Helper Functions
void drawpixel(int x, int y, Uint32 * all_pixels, Uint32 ** tmpPixels/*, SDL_Surface * gPNGSurface, SDL_Window * gWindow, SDL_Surface * gScreenSurface */)
{


    if(x>0 && x<mainwindowWidth && y>0 && y<mainwindowHeight) //keep safe image boundaries
    {
        //next pixel position
        int index = y* mainwindowWidth   + x;

        //Get specific pixel
        Uint32 pixel = (*tmpPixels)[index];

        //Change the current pixel to the values specified by newRed,newGreen,newBlue

        SDL_Color c;c.r=colorpicked.r;c.g=colorpicked.g;c.b=colorpicked.b;
        Uint32 tmpPixel=SDL_MapRGB(mainwindowFormattedSurface->format,c.r,c.g,c.b );

        //Update the buffer surface's pixels
        (*tmpPixels)[y * mainwindowWidth + x] = tmpPixel;

        SDL_SetRenderDrawColor( mainwindowRenderer, colorpicked.a, colorpicked.r, colorpicked.g, colorpicked.b);
        SDL_RenderDrawPoint(mainwindowRenderer,x,y);



//        pixel = (0xFF << 24) | (255 << 16) | (0 << 8) | 0;

//        all_pixels[y * gPNGSurface->w + x] = pixel;
    }



    //Apply the PNG image
//    SDL_BlitSurface( gPNGSurface, NULL, gScreenSurface, NULL );

    //Update the surface
//    SDL_UpdateWindowSurface( gWindow );

}


void callDrawPixel(int xc,int yc,int x,int y, Uint32 * all_pixels, Uint32 ** tmpPixels/*, SDL_Surface * gPNGSurface, SDL_Window * gWindow, SDL_Surface * gScreenSurface*/ )
{

   // Draw 45 arcs from bottom counterclockwise
   drawpixel(xc+x, yc+y, all_pixels, tmpPixels/*,gPNGSurface,gWindow,gScreenSurface*/);
   drawpixel(xc+x, yc-y, all_pixels, tmpPixels/*gPNGSurface,gWindow,gScreenSurface*/);
   drawpixel(xc+y, yc+x, all_pixels, tmpPixels/*,gPNGSurface,gWindow,gScreenSurface*/);
   drawpixel(xc+y, yc-x, all_pixels, tmpPixels/*,gPNGSurface,gWindow,gScreenSurface*/);

   drawpixel(xc-x, yc-y, all_pixels, tmpPixels/*,gPNGSurface,gWindow,gScreenSurface*/);
   drawpixel(xc-x, yc+y, all_pixels, tmpPixels/*,gPNGSurface,gWindow,gScreenSurface*/);
   drawpixel(xc-y, yc-x, all_pixels, tmpPixels/*,gPNGSurface,gWindow,gScreenSurface*/);
   drawpixel(xc-y, yc+x, all_pixels, tmpPixels/*,gPNGSurface,gWindow,gScreenSurface*/);
}


void drawCircles(int brushRadius, int mouseY, int mouseX)
{
    const double PI = 3.14159;

    //circle radius
    for (int incrRadius=0; incrRadius<brushRadius; incrRadius++)
    {
        //draw a circle
        for (double angle=0; angle<=2*PI; angle+=0.001)//You are using radians so you will have to increase by a very small amount
        {
            //This will have the coordinates  you want to draw a point at

             Uint32 pix=SDL_MapRGB(mainwindowFormattedSurface->format,colorpicked.r,colorpicked.g,colorpicked.b);
             mainwindowPixels[ (int)(mouseY + incrRadius*sin( angle )) * mainwindowWidth + (int)(mouseX + incrRadius*cos( angle )) ] = pix;

             // how it's done
//             SDL_SetRenderDrawColor(mainwindowRenderer, colorpicked.r, colorpicked.g, colorpicked.b, colorpicked.a);
//             SDL_RenderDrawPoint(mainwindowRenderer,mouseX + incrRadius*sin( angle ), mouseY + incrRadius*cos( angle ));
//             SDL_RenderPresent(mainwindowRenderer);
        }

    }
}

void drawMultipleInnerCircles(int r, int x, int y, int yc, int xc, float Pk, Uint32 * all_pixels, Uint32 ** tmpPixels, boolean &changeLocation, boolean &enterWhile/*, SDL_Surface *gPNGSurface, SDL_Window *gWindow, SDL_Surface * gScreenSurface */)
{
//    while (r>=0 && enterWhile)
    {
        // main drawing pixels loop
        while(x<y && enterWhile)
        {
            if (Pk<0)
            {
                x=x+1;
                Pk=Pk+(2*x)+1;
            }
            else
            {
                x=x+1;
                y=y-1;
                Pk=Pk+(2*x)-(2*y)+1;
            }
            callDrawPixel(xc,yc,x,y, all_pixels, tmpPixels/*,gPNGSurface,gWindow,gScreenSurface*/);

        }

        //allow for a second circle to be created
    //                        enterWhile=false;

        changeLocation=TRUE;
        x=1;
        y=--r;
        Pk=1-r;
    }

//    if (changeLocation)
//    {
//        r=50;
//        x=1;
//        y=--r;
//        Pk=1-r;
//        changeLocation=false;
//    }

}


typedef struct Point
{
    Point(){;}
    Point(int _x,int _y){x=_x;y=_y;}
    ~Point(){}
    Point(const Point &_p){x=_p.x;y=_p.y;}
    void operator=(const Point &_p){x=_p.x;y=_p.y;}

    int x,y;
}p;


#include <stack>
typedef struct Element
{
    Element() {  ; }
    Element(int _x,int _y)
    {
        x=_x;
        y=_y;
    }
    ~Element(){}

 int x;
 int y;
}Element;



static int counter=0;

void floodfill (int x,int  y, Uint32* all_pixels, Uint8 targetR,Uint8 targetG,Uint8 targetB, Uint8 replacementR ,Uint8 replacementG,Uint8 replacementB)
{
    std::stack<Element> stack;


    Uint32 * tmpPixels=(Uint32*)malloc(mainwindowWidth*mainwindowHeight* sizeof(Uint32));
    memcpy(tmpPixels,all_pixels, mainwindowWidth * mainwindowHeight * sizeof(Uint32));


//    int pitch;
//    void *pxs=(void *) all_pixels;
//    SDL_LockTexture(mainwindowTexture,NULL,&pxs,&pitch);

    Element e(x,y);
    stack.push(e);

        while( (stack.size()) > 0 )
        {

            Element e = stack.top(); stack.pop();
            x= e.x;
            y= e.y;

//            std::cout<<"x="<<x<<", y="<<y<<std::endl;

            //make sure pixel position is within the surface's boundaries
            if  (x > 0 && x < mainwindowWidth && y > 0 && y < mainwindowHeight)
            {

                //next pixel position
                int index = y* mainwindowWidth   + x;

                //Get specific pixel
                Uint32 pixel = tmpPixels[index];

                Uint8 curPixR, curPixG, curPixB;
                //Get current r,g,b

//                Uint32 *pixelformat;
//                int w,h;
//                SDL_QueryTexture(mainwindowTexture, pixelformat, NULL, &w, &h);




                SDL_GetRGB(pixel, mainwindowFormattedSurface->format , &curPixR, &curPixG, &curPixB);




                //We only change the color picked up by the mouse at pixel location we clicked
                // If the node's color we visit doesn't match the color we target to change we simply continue
                if( (curPixR!=targetR || curPixG!=targetG || curPixB!=targetB) )
                {
                        continue;
                }
                if( (curPixR==replacementR && curPixG==replacementG && curPixB==replacementB) )
                {
                        break;
                }

                //if we have just hit the pixel that we intend to change the colour of
                {//if we have just hit the pixel that we intend to change the colour of
//                {
                    //Change the current pixel to the values specified by newRed,newGreen,newBlue
//                    pixel = (0xFF << 24) | (replacementR << 16) | (replacementG << 8) | replacementB;
                    //Update the surface's pixels
//                    all_pixels[y * mainwindowWidth + x] = pixel;


                    SDL_Color c;c.r=replacementR;c.g=replacementG;c.b=replacementB;
                    Uint32 tmpPixel=SDL_MapRGB(mainwindowFormattedSurface->format,c.r,c.g,c.b );

//                    for(int i =0;i<mainwindowWidth;i++)
//                        for(int j =0;j<mainwindowHeight;j++)
                            tmpPixels[y * mainwindowWidth + x] = tmpPixel;


                    stack.push( Element(x + 1, y) );  // right
                    stack.push( Element(x - 1, y) );  // left
                    stack.push( Element(x, y + 1) );  // down
                    stack.push( Element(x, y - 1) );  // up

                }
            }
    }

        memcpy(all_pixels,tmpPixels,mainwindowWidth*mainwindowHeight* sizeof(Uint32));
        delete tmpPixels;

//        SDL_UnlockTexture(mainwindowTexture);


}


////Recursive 4-way floodfill, crashes if recursion stack is full
//void floodFill4(int x, int y, Uint32* all_pixels, Uint8 targetR,Uint8 targetG,Uint8 targetB, Uint8 replacementR ,Uint8 replacementG,Uint8 replacementB)
//{
//    //Make sure we 're within the bounbaries of our surface & that the current pixel's color
//    //  is 0,0,0,


//    if( x >= 0 && x < mainwindowWidth && y >= 0 && y < mainwindowHeight )
//    {
//        //next pixel position
//        int index = y* mainwindowWidth  + x;

//        //Get specific pixel
//        Uint32 pixel = all_pixels[index];

//        Uint8 curPixR, curPixG, curPixB;
//        //Get current r,g,b
//        SDL_GetRGB(pixel, toolsFormattedSurface->format, &curPixR, &curPixG, &curPixB);

//        // the node's color we visit must match match the color                                 the node's color we visit must match not have the same
//        // we intend to change (looking for in ex. white pixels)                                 color as the new color (in ex. "don't make it")
//        if( (curPixR==targetR && curPixG==targetG && curPixB==targetB) && (curPixR!=replacementR || curPixG!=replacementG || curPixB!=replacementB))
//        {
//            //Change the current pixel to the values specified by newRed,newGreen,newBlue
////            pixel = (0xFF << 24) | (replacementR << 16) | (replacementG << 8) | replacementB;
////            //Update the surface's pixels
////            all_pixels[y * mainwindowWidth+ x] = pixel;

//            SDL_Color c;c.r=replacementR;c.g=replacementG;c.b=replacementB;
//            Uint32 tmpPixel=SDL_MapRGB(toolsFormattedSurface->format,c.r,c.g,c.b );
//            all_pixels[y * mainwindowWidth+ x] = tmpPixel;


//            floodFill4(x + 1, y,     all_pixels,  targetR,targetG,targetB, replacementR,replacementG,replacementB );
//            floodFill4(x - 1, y,     all_pixels,  targetR,targetG,targetB, replacementR,replacementG,replacementB );
//            floodFill4(x,     y + 1, all_pixels,  targetR,targetG,targetB, replacementR,replacementG,replacementB );
//            floodFill4(x,     y - 1, all_pixels,  targetR,targetG,targetB, replacementR,replacementG,replacementB );
//        }

//    }
//}




Point lineStart;
Point lineEnd;

void drawBresenhamLine(int x,int y,int x2,int y2)
{
      Point * lineArray=NULL;
      lineArray=(Point*)malloc(1*sizeof(Point));


      //http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/

      int w = x2 - x ;
      int h = y2 - y ;
      int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
      if (w<0) dx1 = -1 ; else if (w>0) dx1 = 1 ;
      if (h<0) dy1 = -1 ; else if (h>0) dy1 = 1 ;
      if (w<0) dx2 = -1 ; else if (w>0) dx2 = 1 ;

      int longest = abs(w) ;
      int shortest = abs(h) ;

      if (!(longest>shortest))
      {
          longest = abs(h) ;
          shortest = abs(w) ;
          if (h<0) dy2 = -1 ;
          else if (h>0) dy2 = 1 ;
          dx2 = 0 ;
      }
      int numerator = longest >> 1 ;
      for (int i=0;i<=longest;i++)
      {
          SDL_SetRenderDrawColor(mainwindowRenderer, colorpicked.r, colorpicked.g, colorpicked.b, colorpicked.a);
          SDL_RenderDrawPoint(mainwindowRenderer,x,y);

          lineArray=(Point*)realloc(lineArray,(i+1)*sizeof(Point));
          lineArray[i]=Point(x,y);


//          std::cout<<"lineArray="<<lineArray[i].x<<","<<lineArray[i].y<<std::endl;

          numerator += shortest ;
          if (!(numerator<longest))
          {
              numerator -= longest ;
              x += dx1 ;
              y += dy1 ;
          } else {
              x += dx2 ;
              y += dy2 ;
          }
      }


    //clear our buffer constantly so as to end up with only 1 line



    //Now create the backbuffercopy of the original pixel array (our board)
    memcpy(backbufferPixels, mainwindowPixels,  mainwindowWidth * mainwindowHeight * sizeof(Uint32));

    //create a a pixel based on the color chosen
    Uint32 tmpPixel=SDL_MapRGB(mainwindowFormattedSurface->format, colorpicked.r,colorpicked.g,colorpicked.b);
    for(int i=0;i<=longest;i++)
    {
        //replace backbuffer pixel with it
        backbufferPixels[lineArray[i].y * mainwindowWidth + lineArray[i].x]=tmpPixel;
    }

    free(lineArray);



////    Point lineArray[100]={Point(0,0)};

//      int lineArrayElements=0;
//      Point * lineArray=NULL;
//      lineArray=(Point*)malloc(1*sizeof(Point));
//      lineArrayElements++;
//      int dx=x1-x0;
//      int dy=y1-y0;

//      int D = 2*dy - dx;
//      lineArray[0]=Point(x0,y0);;
//      int y=y0;

////      if (D > 0)
////      {
////          y = y+1;
////          D = D - (2*dx);
////      }

//      for(int x=x0+1;x<=x1;x++)
//      {
//          lineArray=(Point*)realloc(lineArray,(x+1)*sizeof(Point));
//          lineArray[x]=Point(x,y);
//          D = D + (2*dy);
//          if (D > 0)
//          {
//            y = y+1;
//            D = D - (2*dx);
//          }
//          lineArrayElements++;
//      }


//      for(int i=0;i<lineArrayElements;i++)
//      {
//          Point tmpPlotingPoint=lineArray[i];

//          SDL_SetRenderDrawColor( mainwindowRenderer, 0, 0, 255, 255 );

//          //back buffer draw points
//          SDL_RenderDrawPoint(mainwindowRenderer,tmpPlotingPoint.x,tmpPlotingPoint.y);
////          SDL_Color pointcolor;
////          pointcolor.r=0;pointcolor.g=255;pointcolor.b=0;
////          Uint32 tmpPixel=SDL_MapRGB(toolsFormattedSurface->format, pointcolor.r,pointcolor.g,pointcolor.b);
////          backbufferPixels[tmpPlotingPoint.y * mainwindowWidth + tmpPlotingPoint.x]=tmpPixel;

//      }


//      free(lineArray);

}



int main(int argc, char ** argv)
{

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * drawingWindow = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mainwindowWidth, mainwindowHeight, 0);
    int drawingWindowId=SDL_GetWindowID(drawingWindow);

    mainwindowRenderer = SDL_CreateRenderer(drawingWindow, -1, 0);
    mainwindowTexture = SDL_CreateTexture(mainwindowRenderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, mainwindowWidth, mainwindowHeight);


    SDL_Window * toolsWindow = SDL_CreateWindow("Tools",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, toolswindowWidth, toolswindowWidth, 0);
    int ToolsWindowId=SDL_GetWindowID(toolsWindow);

    toolsRenderer = SDL_CreateRenderer(toolsWindow, -1, 0);

    toolsSurface=IMG_Load(toolPath);
    if( toolsSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", toolPath, IMG_GetError() );
    }
    else
    {
        // Convert surface to display format

        // toolsFormattedSurface = SDL_ConvertSurface( toolsSurface,  SDL_GetWindowSurface(gWindow)->format, NULL );
        toolsFormattedSurface = SDL_ConvertSurfaceFormat( toolsSurface, SDL_PIXELFORMAT_ARGB8888, NULL );

        if( toolsFormattedSurface == NULL )
        {
            printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Create blank streamable toolsTexture
            toolsTexture = SDL_CreateTexture( toolsRenderer,SDL_GetWindowPixelFormat( toolsWindow ), SDL_TEXTUREACCESS_STATIC, toolswindowWidth, toolswindowWidth );

            if( toolsTexture == NULL )
            {
                printf( "Unable to create blank toolsTexture! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                int pitch;
                //Lock toolsTexture for manipulation
                SDL_LockTexture( toolsTexture, NULL, &toolsPixels, &pitch );

                //Copy loaded/formatted surface pixels
                memcpy( toolsPixels, toolsFormattedSurface->pixels, toolsFormattedSurface->pitch * toolsFormattedSurface->h );


                //Unlock toolsTexture to update
                SDL_UnlockTexture( toolsTexture );
//                    toolsPixels = NULL;
            }

        }
        //Get rid of old loaded surface
        SDL_FreeSurface( toolsSurface );
    }
    //////////////////////////////////////////////////////////////////

    Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    mainwindowSurface = SDL_CreateRGBSurface(0,mainwindowWidth,mainwindowHeight,32, rmask, gmask, bmask, amask);
    mainwindowFormattedSurface = SDL_ConvertSurfaceFormat( mainwindowSurface, SDL_PIXELFORMAT_ARGB8888, NULL );
    if( mainwindowFormattedSurface == NULL )
    {
        printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
//            int pitch;
//            void *pxs=(void*)mainwindowPixels;
//            //Lock mainwindowTexture for manipulation
//            SDL_LockTexture( mainwindowTexture, NULL, &pxs, &pitch );

//            //Copy loaded/formatted surface pixels
//            memcpy( mainwindowPixels, mainwindowFormattedSurface->pixels, mainwindowWidth *mainwindowHeight );

//            //Unlock mainwindowTexture to update
//            SDL_UnlockTexture( mainwindowTexture );

    }
    //Get rid of old loaded surface
    SDL_FreeSurface( mainwindowSurface );


    memset(mainwindowPixels, 255, mainwindowWidth * mainwindowHeight * sizeof(Uint32));

    //copy
    SDL_UpdateTexture(toolsTexture, NULL, toolsPixels, toolswindowWidth * sizeof(Uint32));

    while (!quit)
    {
        SDL_UpdateTexture(mainwindowTexture, NULL, mainwindowPixels, mainwindowWidth * sizeof(Uint32));

        SDL_PollEvent(&event);

//        SDL_Rect DestR;
//        DestR.x = 100;
//        DestR.y = 100;
//        DestR.w = 100;
//        DestR.h = 100;

        switch (event.type)
        {
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                leftMouseButtonDown = false;

                //Decision made- Now mouse is up, so copy to original 'pixel' data the buffered data.
                std::cout<<"drawPointLine="<<drawPointLine<<std::endl;

                if (drawPointLine && backbufferPixels!=NULL)
                {
                    memcpy(mainwindowPixels,backbufferPixels,mainwindowWidth*mainwindowHeight*sizeof(Uint32));

                    delete backbufferPixels;
                    backbufferPixels=NULL;

                }

                if (drawPointCircle && backbufferPixels!=NULL)
                {
                    memcpy(mainwindowPixels,backbufferPixels,mainwindowWidth*mainwindowHeight*sizeof(Uint32));

                    delete backbufferPixels;
                    backbufferPixels=NULL;
                }



                NOWDRAWING=FALSE;

//                for(int i=0;i<sizeofbackbufferPixels;i++)
//                {
//                    Uint8 r ;
//                    Uint8 g ;
//                    Uint8 b ;


//                    SDL_GetRGB(p,toolsFormattedSurface->format,&r,&g,&b);

//                    Uint32 pix=SDL_MapRGB(toolsFormattedSurface->format,r,g,b);

//                    pixels[(i) * mainwindowWidth + i] = pix;//(0xFF << 24) | (tmpColor << 16) | (tmpColor << 8) | tmpColor;;
//                }

            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
                leftMouseButtonDown = true;
        case SDL_MOUSEMOTION:
            if (leftMouseButtonDown)
            {

                if(event.window.windowID==drawingWindowId)
                {
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;



                    //Now draw the rectangle on the top
//                    SDL_Rect r;
//                    r.x = 50;
//                    r.y = 50;
//                    r.w = 50;
//                    r.h = 50;
//                    // Set render color to blue ( rect will be rendered in this color )
//                    SDL_SetRenderDrawColor( mainwindowRenderer, 0, 0, 255, 255 );
//                    // Render rect
//                    SDL_RenderDrawRect( mainwindowRenderer, &r );





//                    std::cout<<drawPointLine<<std::endl;

                    if (drawPointLine==TRUE)
                    {
                        //Line Drawing
                        //Make sure we draw the mainwindowTexture and THEN..we draw on the top of it for the backbuffer lines,points (for circle,rectangle)
                        SDL_RenderCopy(mainwindowRenderer, mainwindowTexture, NULL, NULL);

                        Point currentmousePos(mouseX,mouseY);
                        //start line point initialized just once
                        if (!NOWDRAWING)
                        {
                            NOWDRAWING=TRUE;
                            lineStart=currentmousePos;
                        }

                        std::cout<<lineStart.x<<","<<lineStart.y<<std::endl;

                        //end line point
                        lineEnd=currentmousePos;

                        //Allocate some memory for the backbufferPixels
                        if (backbufferPixels==NULL)
                        {
                            backbufferPixels=(Uint32*)malloc(mainwindowWidth*mainwindowHeight* sizeof(Uint32));
                        }
                        else
                        {
                            memset(backbufferPixels,0,mainwindowWidth*mainwindowHeight* sizeof(Uint32));
                        }

                        //Now create the backbuffercopy of the original pixel array (our main drawing board)
//                        memcpy(backbufferPixels, pixels,  mainwindowWidth * mainwindowHeight * sizeof(Uint32));

                        drawBresenhamLine(lineStart.x,lineStart.y, lineEnd.x,lineEnd.y);


//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                        //back buffer draw points
//                        SDL_RenderDrawPoint(mainwindowRenderer,mouseX,mouseY);
//                        SDL_Color pointcolor;
//                        pointcolor.r=0;pointcolor.g=255;pointcolor.b=0;
//                        Uint32 tmpPixel=SDL_MapRGB(toolsFormattedSurface->format, pointcolor.r,pointcolor.g,pointcolor.b);
//                        backbufferPixels[mouseY * mainwindowWidth + mouseX]=tmpPixel;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //draw line of 50 points 0,0,to 50,50
//                        for (int i=0;i<50;i++)
//                        {
//                                backbufferPixels=NULL;
//                                backbufferPixels= (Uint32*)malloc(10*sizeof(Uint32));
//                                SDL_SetRenderDrawColor( mainwindowRenderer, 0, 0, 255, 255 );
//                                SDL_RenderDrawPoint(mainwindowRenderer,i,i);

//                                backbufferPixels = (Uint32*) realloc (backbufferPixels, i*sizeof(Uint32));

//                                SDL_Color pointcolor;
//                                pointcolor.r=0;pointcolor.g=255;pointcolor.b=0;
//                                Uint32 tmpPixel=SDL_MapRGB(toolsFormattedSurface->format, pointcolor.r,pointcolor.g,pointcolor.b);
//                                backbufferPixels[mouseY * mainwindowWidth + mouseX]=tmpPixel;
//                                sizeofbackbufferPixels=i;
//                        }

                    }
                    else if (drawRectangle==TRUE)
                    {

                    }
                    else if (drawPointCircle==TRUE)
                    {

                        //Line Drawing
                        //Make sure we draw the mainwindowTexture and THEN..we draw on the top of it for the backbuffer lines,points (for circle,rectangle)
                        SDL_RenderCopy(mainwindowRenderer, mainwindowTexture, NULL, NULL);

                        Point currentmousePos(mouseX,mouseY);
                        //start line point initialized just once
                        if (!NOWDRAWING)
                        {
                            NOWDRAWING=TRUE;
                            lineStart=currentmousePos;
                        }
                        //end line point
                        lineEnd=currentmousePos;

                        //Now we need to calculate r based on the lineStart,lineEnd
//                        if (!(lineEnd.x-lineStart.x==0 && lineEnd.y-lineStart.y==0))
                        {
                            //find length of r based on 2 points
                            int r=sqrt( pow((lineEnd.x-lineStart.x),2) + pow((lineEnd.y-lineStart.y),2) );

                            boolean enterWhile=TRUE;
                            boolean changeLocation=FALSE;
//                            int r=50;
                            //mid circle point found
                            int xc=(lineEnd.x+lineStart.x)/2;//initial x,y values
                            int yc=(lineEnd.y+lineStart.y)/2;//initial x,y values
                            int x=1;
                            int y=r;
                            float Pk=1-r;

                            if (backbufferPixels==NULL)
                            {
                                backbufferPixels=(Uint32*)malloc(mainwindowWidth*mainwindowHeight* sizeof(Uint32));
                            }
                            else
                            {
                                memset(backbufferPixels,0,mainwindowWidth*mainwindowHeight* sizeof(Uint32));
                            }

                            memcpy(backbufferPixels,mainwindowPixels, mainwindowWidth * mainwindowHeight * sizeof(Uint32));

                            drawMultipleInnerCircles(r, x,  y, yc ,  xc, Pk, mainwindowPixels, &backbufferPixels, changeLocation, enterWhile/*, gPNGSurface, gWindow, gScreenSurface*/);


                        }
                    }
                    else if (drawPointBucketFill==TRUE)
                    {
                        if (!NOWDRAWING)
                        {
                            NOWDRAWING=TRUE;

                            if(mouseX!=-1 && mouseY!=-1)
                            {
                                Uint8 red,green,blue;
                                Uint8 newRed,newGreen,newBlue;

                                //Grab the color of the pixel on the spot and change the pixel's that match this color
                                int index =(mouseY) * mainwindowWidth + mouseX;
                                Uint32 pixel = mainwindowPixels[index];

                                SDL_GetRGB(pixel, mainwindowFormattedSurface->format, &red, &green, &blue);

                                SDL_Color c;c.r=red;c.g=green;c.b=blue;


                                //Flood-Fill with Yellow Colour
                                newRed=colorpicked.r;
                                newGreen=colorpicked.g;
                                newBlue=colorpicked.b;
                                SDL_Color nc;nc.r=newRed;nc.g=newGreen;nc.b=newBlue;


    //                            floodFill4(mouseX,mouseY,mainwindowPixels,red,green,blue, newRed,newGreen,newBlue);
                                floodfill(mouseX,mouseY,mainwindowPixels, c.r,c.g,c.b, nc.r,nc.g,nc.b);

                            }
                        }

                    }
                    else if (drawPointPencil==TRUE)
                    {
                        //Line Drawing
                        //Make sure we draw the mainwindowTexture and THEN..we draw on the top of it for the backbuffer lines,points (for circle,rectangle)
                        SDL_RenderCopy(mainwindowRenderer, mainwindowTexture, NULL, NULL);

                        Uint32 pix=SDL_MapRGB(mainwindowFormattedSurface->format,colorpicked.r,colorpicked.g,colorpicked.b);
                        mainwindowPixels[(mouseY) * mainwindowWidth + mouseX] = pix;//(0xFF << 24) | (tmpColor << 16) | (tmpColor << 8) | tmpColor;;

                    }
                    else if (drawPointBrush==TRUE)
                    {
                        //Line Drawing
                        //Make sure we draw the mainwindowTexture and THEN..we draw on the top of it for the backbuffer lines,points (for circle,rectangle)
                        SDL_RenderCopy(mainwindowRenderer, mainwindowTexture, NULL, NULL);

                        //Create a brush (draws on surrounding pixels as well depending on the brushsize)
                        int brushsize=8;
//                        for(int i=0;i<brushsize/2;i++)
//                        {
//                            for(int j=0;j<brushsize/2;j++)
//                            {
//                                Uint32 pix=SDL_MapRGB(mainwindowFormattedSurface->format,colorpicked.r,colorpicked.g,colorpicked.b);

//                                mainwindowPixels[(mouseY+j) * mainwindowWidth + mouseX+i] = pix;
//                            }
//                        }

                        drawCircles(brushsize, mouseY, mouseX);


                    }
                    else if (drawPointEraser==TRUE)
                    {
                        //Line Drawing
                        //Make sure we draw the mainwindowTexture and THEN..we draw on the top of it for the backbuffer lines,points (for circle,rectangle)
                        SDL_RenderCopy(mainwindowRenderer, mainwindowTexture, NULL, NULL);


                        //Create a brush (draws on surrounding pixels as well depending on the brushsize)
                        int brushsize=8;
                        for(int i=0;i<brushsize/2;i++)
                        {
                            for(int j=0;j<brushsize/2;j++)
                            {
                                Uint32 pix=SDL_MapRGB(mainwindowFormattedSurface->format,colorpicked.r,colorpicked.g,colorpicked.b);

                                mainwindowPixels[(mouseY+j) * mainwindowWidth + mouseX+i] = pix;//(0xFF << 24) | (tmpColor << 16) | (tmpColor << 8) | tmpColor;;
                            }
                        }
                    }


//                    //draw rectangle
//                    if (drawRectangle==TRUE)
//                    {
//                        int brushsize=8;
//                        for(int i=0;i<brushsize/2;i++)
//                        {
//                            for(int j=0;j<brushsize/2;j++)
//                            {
//                                Uint8 r ;
//                                Uint8 g ;
//                                Uint8 b ;
//                                r=0;g=255;b=0;
//    //                            tmpColor=r+g+b;
//    //                            =(0xFF << 24) | (tmpColor << 16) | (tmpColor << 8) | tmpColor;

//                                Uint32 pix=SDL_MapRGB(toolsFormattedSurface->format,r,g,b);

//                                pixels[(mouseY+j) * mainwindowWidth + mouseX+i] = pix;//(0xFF << 24) | (tmpColor << 16) | (tmpColor << 8) | tmpColor;;
//                            }
//                        }
//                    }


                }
                else if(event.window.windowID==ToolsWindowId)
                {

                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;

                    //Declare temporary color channels
                    Uint8 r ;
                    Uint8 g ;
                    Uint8 b ;

                    //convert void * to Uint32  array, for direct pixel array manipulation
                    Uint32 *pxls= (Uint32*)toolsPixels;

                    //Get a specific pixel and check its color
                    Uint32 p=pxls[mouseY * toolswindowWidth + mouseX];
                    SDL_GetRGB(p,toolsFormattedSurface->format, &r,&g,&b);;

                    std::cout<<"mouseX="<<mouseX<<" , "<<"mouseY="<<mouseY<<std::endl;

                    //Select Line Drawing Tool based on the color of the pixel clicked
//                    if (r==0 &&g==0 &&b==0)

                    //Select Line Drawing Tool based on which portion of the mainwindowTexture the mouse clicks

                    //RECTANGLE
                    if (mouseX>0 && mouseX<30 && mouseY>0 && mouseY<30)
                    {
                        std::cout<<"RECTANGLE portion of mainwindowTexture"<<std::endl;
                        drawRectangle=TRUE;
                        drawPointLine=FALSE;
                        drawPointBrush=FALSE;
                        drawPointBucketFill=FALSE;
                        drawPointCircle=FALSE;
                        drawPointEraser=FALSE;
                        drawPointPencil=FALSE;
                        drawPointRedColor =FALSE;
                        drawPointBlackColor =FALSE;



//                        r=255;g=255;b=255;
//                        tmpColor = r + g + b;
//                        pxls[mouseY * toolswindowWidth + mouseX] = SDL_MapRGB(toolsFormattedSurface->format,r,g,b);//(0xFF << 24) | (tmpColor << 16) | (tmpColor << 8) | tmpColor;
                    }
                    //CIRCLE
                    else if (mouseX>30 && mouseX<60 && mouseY>0 && mouseY<30)
                    {
                        std::cout<<"CIRCLE portion of mainwindowTexture"<<std::endl;

                        drawRectangle=FALSE;
                        drawPointLine=FALSE;
                        drawPointBrush=FALSE;
                        drawPointBucketFill=FALSE;
                        drawPointCircle=TRUE;
                        drawPointEraser=FALSE;
                        drawPointPencil=FALSE;
                        drawPointRedColor =FALSE;
                        drawPointBlackColor =FALSE;

//                        r=0;g=0;b=0;
//                        tmpColor = r + g + b;
//                        pxls[mouseY * toolswindowWidth + mouseX] = SDL_MapRGB(toolsFormattedSurface->format,r,g,b);;//(0xFF << 24) | (tmpColor << 16) | (tmpColor << 8) | tmpColor;
                    }
                    //BUCKET FILL
                    else if (mouseX>60 && mouseX<toolswindowWidth && mouseY>0 && mouseY<30)
                    {
                        std::cout<<"BUCKET FILL portion of mainwindowTexture"<<std::endl;

                        drawRectangle=FALSE;
                        drawPointLine=FALSE;
                        drawPointBrush=FALSE;
                        drawPointBucketFill=TRUE;
                        drawPointCircle=FALSE;
                        drawPointEraser=FALSE;
                        drawPointPencil=FALSE;
                        drawPointRedColor =FALSE;
                        drawPointBlackColor =FALSE;
                    }
                    //LINE
                    else if (mouseX>0 && mouseX<30 && mouseY>30 && mouseY<60)
                    {
                        std::cout<<"LINE portion of mainwindowTexture"<<std::endl;

                        drawRectangle=FALSE;
                        drawPointLine=TRUE;
                        drawPointBrush=FALSE;
                        drawPointBucketFill=FALSE;
                        drawPointCircle=FALSE;
                        drawPointEraser=FALSE;
                        drawPointPencil=FALSE;
                        drawPointRedColor =FALSE;
                        drawPointBlackColor =FALSE;
                    }
                    //PENCIL
                    else if (mouseX>30 && mouseX<60 && mouseY>30 && mouseY<60)
                    {
                        std::cout<<"PENCIL portion of mainwindowTexture"<<std::endl;

                        drawRectangle=FALSE;
                        drawPointLine=FALSE;
                        drawPointBrush=FALSE;
                        drawPointBucketFill=FALSE;
                        drawPointCircle=FALSE;
                        drawPointEraser=FALSE;
                        drawPointPencil=TRUE;
                        drawPointRedColor =FALSE;
                        drawPointBlackColor =FALSE;
                    }
                    //BRUSH
                    else if (mouseX>60 && mouseX<toolswindowWidth && mouseY>30 && mouseY<60)
                    {
                        std::cout<<"BRUSH portion of mainwindowTexture"<<std::endl;

                        drawRectangle=FALSE;
                        drawPointLine=FALSE;
                        drawPointBrush=TRUE;
                        drawPointBucketFill=FALSE;
                        drawPointCircle=FALSE;
                        drawPointEraser=FALSE;
                        drawPointPencil=FALSE;
                        drawPointRedColor =FALSE;
                        drawPointBlackColor =FALSE;
                    }
                    //RED COLOR
                    else if (mouseX>0 && mouseX<30 && mouseY>60 && mouseY<toolswindowWidth)
                    {
                        std::cout<<"RED COLOR portion of mainwindowTexture"<<std::endl;

                        drawRectangle=FALSE;
                        drawPointLine=FALSE;
                        drawPointBrush=FALSE;
                        drawPointBucketFill=FALSE;
                        drawPointCircle=FALSE;
                        drawPointEraser=FALSE;
                        drawPointPencil=FALSE;
                        drawPointRedColor =TRUE;
                        drawPointBlackColor =FALSE;

                        colorpicked.r=255;colorpicked.g=0;colorpicked.b=0;
                    }
                    //BLACK COLOR
                    else if (mouseX>30 && mouseX<60 && mouseY>60 && mouseY<toolswindowWidth)
                    {
                        std::cout<<"BLACK COLOR portion of mainwindowTexture"<<std::endl;

                        drawRectangle=FALSE;
                        drawPointLine=FALSE;
                        drawPointBrush=FALSE;
                        drawPointBucketFill=FALSE;
                        drawPointCircle=FALSE;
                        drawPointEraser=FALSE;
                        drawPointPencil=FALSE;
                        drawPointRedColor =FALSE;
                        drawPointBlackColor =TRUE;

                        colorpicked.r=0;colorpicked.g=0;colorpicked.b=0;
                    }
                    //ERASER
                    else if (mouseX>60 && mouseX<toolswindowWidth && mouseY>60 && mouseY<toolswindowWidth)
                    {
                        std::cout<<"ERASER portion of mainwindowTexture"<<std::endl;

                        drawRectangle=FALSE;
                        drawPointLine=FALSE;
                        drawPointBrush=FALSE;
                        drawPointBucketFill=FALSE;
                        drawPointCircle=FALSE;
                        drawPointEraser=TRUE;
                        drawPointPencil=FALSE;
                        drawPointRedColor =FALSE;
                        drawPointBlackColor =FALSE;

                        colorpicked.r=255;colorpicked.g=255;colorpicked.b=255;
                    }


                }
            }
            break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym==SDLK_ESCAPE)
                    quit = true;
            break;
        }

//        SDL_RenderClear(mainwindowRenderer);
//        SDL_Rect renderQuad;

//        renderQuad.w = DestR.w; renderQuad.h = DestR.h;
//        renderQuad.x=DestR.x;renderQuad.y=DestR.y;

        //use it just a for buffering-rubberband helper-then modify the actuale pixels of the mainwindowTexture when mouse up for example
//        SDL_Rect outlineRect = { 100 , 100, 100, 100 };
//        SDL_SetRenderDrawColor( mainwindowRenderer, 0xFF, 0x00, 0x00, 0xFF );
//        SDL_RenderDrawRect( mainwindowRenderer, &outlineRect );

        // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.

        //update the mainwindow
        if(!leftMouseButtonDown)
        {
            SDL_RenderCopy(mainwindowRenderer, mainwindowTexture, NULL, NULL);
        }


//        int drawAreaWidth=50;
//        int drawAreaHeight=50;
//        SDL_Texture * buffer=SDL_CreateTexture(mainwindowRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,drawAreaWidth,drawAreaHeight);



        //Now draw the rectangle on the top
//        SDL_Rect r;
//        r.x = 50;
//        r.y = 50;
//        r.w = 50;
//        r.h = 50;
//        // Set render color to blue ( rect will be rendered in this color )
//        SDL_SetRenderDrawColor( mainwindowRenderer, 0, 0, 255, 255 );
//        // Render rect
//        SDL_RenderDrawRect( mainwindowRenderer, &r );
//        for (int i=0;i<50;i++)
//        {
//            SDL_RenderDrawPoint(mainwindowRenderer,i,i);
//        }

//        SDL_Rect d;
//        d.x = 50;
//        d.y = 50;
//        d.w = 50;
//        d.h = 50;

//        SDL_RenderCopy(mainwindowRenderer,mainwindowTexture,NULL,&r);


        //update the rendered image
        SDL_RenderPresent(mainwindowRenderer);


        SDL_RenderClear(toolsRenderer);
        SDL_RenderCopy(toolsRenderer, toolsTexture, NULL, NULL);
        SDL_RenderPresent(toolsRenderer);
    }


    SDL_FreeSurface( toolsFormattedSurface );
    SDL_FreeSurface( mainwindowFormattedSurface );

    delete[] mainwindowPixels;
    delete[] toolsPixels;
    SDL_DestroyTexture(mainwindowTexture);
    SDL_DestroyRenderer(mainwindowRenderer);
    SDL_DestroyWindow(drawingWindow);
    SDL_DestroyTexture(toolsTexture);
    SDL_DestroyRenderer(toolsRenderer);
    SDL_DestroyWindow(toolsWindow);
    SDL_Quit();

    return 0;
}


