#include "ingame.h"
#include "them1.h"
#include<sstream>
/// vẽ , tạo khối
void draw_block(SDL_Renderer *rend, Block &b, int red, int green, int blue, int alpha) {
    int x = static_cast<int>(b.x - b.size);
    int y = static_cast<int>(b.y - b.size);
    SDL_Rect r = {x, y, b.size*2, b.size*2};
    SDL_SetRenderDrawColor(rend, red, green, blue, alpha);
    SDL_RenderFillRect(rend, &r);
}
///----------------------------------------------
void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void init_state(State &s, int stage) {

    s.w = 800;
    s.h = 600;
    s.PLAYER.b.size = 10;
    s.PLAYER.b.x = s.w / 2;
    s.PLAYER.b.y = s.h - 2 * s.PLAYER.b.size;

    s.danban.x = 0;
    s.danban.y = s.h*2;
    s.danban.size = 4;
    s.bantrung = true;

    /// Enemies
    for (int i = 0; i < s.N; i++) {
        s.quandich[i].song = false;
    }

    int enemy_size = 20;
    int ww = 5; // so quan dich hang ngang
    int hh = 2; // so quan dich hang doc
    for(int i = 0 ;i < ww; ++i)
    for(int j = 0;j < hh; ++j){
                int index = i + j*ww;
                s.quandich[index].song = true;
                s.quandich[index].chet = false;
                s.quandich[index].b.x =  i*180 + 100;
                s.quandich[index].b.y =  j*200 + 100;

                s.quandich[index].b.size = 60;
    }
}
/// hàm kiểm tra chạm nhau
bool collide(const Block &b1, const Block &b2) {
    return  (abs(b1.x - b2.x) < b1.size + b2.size) && (abs(b1.y - b2.y) < b1.size + b2.size);
}
///---------------------------------------------
void update_state(State &s){
    /// đạn bắn
    if (!s.bantrung) {
        s.danban.y -= 100.0 * 0.005;
        if (s.danban.y < 0) {
            s.bantrung = true;
            s.danban.y = s.h*2;
        }
    }

    ///di chuyển quân địch - crazy movement
    for (int i=0; i < s.N; i++) {
        if (s.quandich[i].song){
            if (s.quandich[i].chet){
                /// ban chet quan dich
                s.quandich[i].b.y += 1.0 ;
            }
            /// neu trung dan
            if ( collide (s.quandich[i].b, s.danban) ) {
                if ( !s.quandich[i].chet ){
                    s.quandich[i].chet = true;

                }
                s.bantrung = true;
                s.danban.y = s.h*2;//dan bien mat
            }
        }
    }
}

///-------------------------------------------
void timeleft(SDL_Renderer *rend,SDL_Texture* texture,TTF_Font *font,SDL_Rect srcRest,SDL_Rect desRectt,std::string text){

	TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);
	srcRest.x = 0;
	srcRest.y =  0;

	desRectt.x = 1000;
	desRectt.y = 80;

	desRectt.w = srcRest.w;
	desRectt.h = srcRest.h;
    SDL_RenderCopy(rend, texture, &srcRest,&desRectt);

}
///----------------------------------------------
void render(SDL_Renderer *rend, State &s, SDL_Texture *texture
            ,SDL_Texture *texture_plane,SDL_Texture *texture_bullet
            ,SDL_Texture *texture_00,SDL_Texture *texture_11,SDL_Texture *texture_22,SDL_Texture *texture_33
            ,SDL_Texture *texture_44,SDL_Texture *texture_55,SDL_Texture *texture_66,SDL_Texture *texture_77
            ,SDL_Texture *texture_88,SDL_Texture *texture_99,SDL_Texture *texture_death
            ,int nvkhong,int nvmot,int nvhai,int nvba,int nvbon,int nvnam
            ,SDL_Texture *texture_0,SDL_Texture *texture_1,SDL_Texture *texture_2,SDL_Texture *texture_3,SDL_Texture *texture_4,SDL_Texture *texture_5){

    SDL_Rect sourceRect;
	SDL_Rect desRect;
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = 100 ;
    sourceRect.h = 154 ;

    desRect.x = s.PLAYER.b.x-30;
    desRect.y = s.PLAYER.b.y-30;
    desRect.w = 130;
    desRect.h = 150;
    SDL_RenderCopy(rend, texture_plane, &sourceRect,&desRect);

    /// Quan dich
    SDL_Rect sourceRect00,sourceRect11,sourceRect22,sourceRect33,sourceRect44,sourceRect55,sourceRect66,sourceRect77,sourceRect88,sourceRect99,sourceRectdeath,sourceRect2;
	SDL_Rect desRect00,desRect11,desRect22,desRect33,desRect44,desRect55,desRect66,desRect77,desRect88,desRect99,desRect2,desRectdeath;
    for(int i = 0; i < s.N; i++){
        if (s.quandich[i].song){
            if (s.quandich[i].chet){
                    if(i == nvkhong){
                        sourceRectdeath.x = 0;
                        sourceRectdeath.y = 0;
                        sourceRectdeath.w = 120 ;
                        sourceRectdeath.h = 120;

                        desRectdeath.x = s.quandich[i].b.x - 40;
                        desRectdeath.y = s.quandich[i].b.y - 40;
                        desRectdeath.w = 30;
                        desRectdeath.h = 35;

                        SDL_RenderCopy(rend, texture_0, &sourceRectdeath,&desRectdeath);

                    }
                    if(i == nvmot){
                        sourceRectdeath.x = 0;
                        sourceRectdeath.y = 0;
                        sourceRectdeath.w = 120 ;
                        sourceRectdeath.h = 120;

                        desRectdeath.x = s.quandich[i].b.x - 40;
                        desRectdeath.y = s.quandich[i].b.y - 40;
                         desRectdeath.w = 30;
                        desRectdeath.h = 35;

                        SDL_RenderCopy(rend, texture_1, &sourceRectdeath,&desRectdeath);

                    }
                    if(i == nvhai){
                        sourceRectdeath.x = 0;
                        sourceRectdeath.y = 0;
                        sourceRectdeath.w = 120 ;
                        sourceRectdeath.h = 120;

                        desRectdeath.x = s.quandich[i].b.x - 40;
                        desRectdeath.y = s.quandich[i].b.y - 40;
                         desRectdeath.w = 30;
                        desRectdeath.h = 35;

                        SDL_RenderCopy(rend, texture_2, &sourceRectdeath,&desRectdeath);

                    }
                    if(i == nvba){
                        sourceRectdeath.x = 0;
                        sourceRectdeath.y = 0;
                        sourceRectdeath.w = 120 ;
                        sourceRectdeath.h = 120;

                        desRectdeath.x = s.quandich[i].b.x - 40;
                        desRectdeath.y = s.quandich[i].b.y - 40;
                        desRectdeath.w = 30;
                        desRectdeath.h = 35;

                        SDL_RenderCopy(rend, texture_3, &sourceRectdeath,&desRectdeath);

                    }
                    if(i == nvbon){
                        sourceRectdeath.x = 0;
                        sourceRectdeath.y = 0;
                        sourceRectdeath.w = 120 ;
                        sourceRectdeath.h = 120;

                        desRectdeath.x = s.quandich[i].b.x - 40;
                        desRectdeath.y = s.quandich[i].b.y - 40;
                         desRectdeath.w = 30;
                        desRectdeath.h = 35;

                        SDL_RenderCopy(rend, texture_4, &sourceRectdeath,&desRectdeath);

                    }
                    if(i == nvnam){
                        sourceRectdeath.x = 0;
                        sourceRectdeath.y = 0;
                        sourceRectdeath.w = 120 ;
                        sourceRectdeath.h = 120;

                        desRectdeath.x = s.quandich[i].b.x - 40;
                        desRectdeath.y = s.quandich[i].b.y - 40;
                         desRectdeath.w = 30;
                        desRectdeath.h = 35;

                        SDL_RenderCopy(rend, texture_5, &sourceRectdeath,&desRectdeath);

                    }
            }
            else
                {
                    if(i == 0){
                        sourceRect00.x = 0;
                        sourceRect00.y = 0;
                        sourceRect00.w = 120 ;
                        sourceRect00.h = 120 ;

                        desRect00.x = s.quandich[i].b.x - 40;
                        desRect00.y = s.quandich[i].b.y - 40;
                        desRect00.w = 80;
                        desRect00.h = 150;

                        SDL_RenderCopy(rend, texture_00, &sourceRect00,&desRect00);
                }
                if(i == 1){

                        sourceRect11.x = 0;
                        sourceRect11.y = 0;
                        sourceRect11.w = 120 ;
                        sourceRect11.h = 120 ;

                        desRect11.x = s.quandich[i].b.x - 40;
                        desRect11.y = s.quandich[i].b.y - 40;
                        desRect11.w = 80;
                        desRect11.h = 150;

                        SDL_RenderCopy(rend, texture_11, &sourceRect11,&desRect11);
                }
                if(i == 2){

                        sourceRect22.x = 0;
                        sourceRect22.y = 0;
                        sourceRect22.w = 120 ;
                        sourceRect22.h = 120 ;

                        desRect22.x = s.quandich[i].b.x - 40;
                        desRect22.y = s.quandich[i].b.y - 40;
                        desRect22.w = 80;
                        desRect22.h = 150;

                        SDL_RenderCopy(rend, texture_22, &sourceRect22,&desRect22);
                }
                if(i == 3){

                        sourceRect33.x = 0;
                        sourceRect33.y = 0;
                        sourceRect33.w = 120 ;
                        sourceRect33.h = 120 ;

                        desRect33.x = s.quandich[i].b.x - 40;
                        desRect33.y = s.quandich[i].b.y - 40;
                        desRect33.w = 80;
                        desRect33.h = 150;

                        SDL_RenderCopy(rend, texture_33, &sourceRect33,&desRect33);
                }
                if(i == 5){

                        sourceRect55.x = 0;
                        sourceRect55.y = 0;
                        sourceRect55.w = 120 ;
                        sourceRect55.h = 120 ;

                        desRect55.x = s.quandich[i].b.x - 40;
                        desRect55.y = s.quandich[i].b.y - 40;
                        desRect55.w = 80;
                        desRect55.h = 150;

                        SDL_RenderCopy(rend, texture_55, &sourceRect55,&desRect55);
                }
                if(i == 4){

                        sourceRect44.x = 0;
                        sourceRect44.y = 0;
                        sourceRect44.w = 120 ;
                        sourceRect44.h = 120 ;

                        desRect44.x = s.quandich[i].b.x - 40;
                        desRect44.y = s.quandich[i].b.y - 40;
                        desRect44.w = 80;
                        desRect44.h = 150;

                        SDL_RenderCopy(rend, texture_44, &sourceRect44,&desRect44);
                }
                if(i == 6){

                        sourceRect66.x = 0;
                        sourceRect66.y = 0;
                        sourceRect66.w = 120 ;
                        sourceRect66.h = 120 ;

                        desRect66.x = s.quandich[i].b.x - 40;
                        desRect66.y = s.quandich[i].b.y - 40;
                        desRect66.w = 80;
                        desRect66.h = 150;

                        SDL_RenderCopy(rend, texture_66, &sourceRect66,&desRect66);
                }
                if(i == 7){

                        sourceRect77.x = 0;
                        sourceRect77.y = 0;
                        sourceRect77.w = 120 ;
                        sourceRect77.h = 120 ;

                        desRect77.x = s.quandich[i].b.x - 40;
                        desRect77.y = s.quandich[i].b.y - 40;
                        desRect77.w = 80;
                        desRect77.h = 150;

                        SDL_RenderCopy(rend, texture_77, &sourceRect77,&desRect77);
                }
                if(i == 8){

                        sourceRect88.x = 0;
                        sourceRect88.y = 0;
                        sourceRect88.w = 120 ;
                        sourceRect88.h = 120 ;

                        desRect88.x = s.quandich[i].b.x - 40;
                        desRect88.y = s.quandich[i].b.y - 40;
                        desRect88.w = 80;
                        desRect88.h = 150;

                        SDL_RenderCopy(rend, texture_88, &sourceRect88,&desRect88);
                }
                if(i == 9){

                        sourceRect99.x = 0;
                        sourceRect99.y = 0;
                        sourceRect99.w = 120 ;
                        sourceRect99.h = 120 ;

                        desRect99.x = s.quandich[i].b.x - 40;
                        desRect99.y = s.quandich[i].b.y - 40;
                        desRect99.w = 80;
                        desRect99.h = 150;

                        SDL_RenderCopy(rend, texture_99, &sourceRect99,&desRect99);
                }
                }
        }
    }

    /// Bullet
    sourceRect2.x = 0;
    sourceRect2.y = 0;
    sourceRect2.w = 60 ;
    sourceRect2.h = 60 ;

    desRect2.x = s.danban.x - 20;
    desRect2.y = s.danban.y - 20;
    desRect2.w = 60;
    desRect2.h = 40;
    SDL_RenderCopy(rend, texture_bullet, &sourceRect2,&desRect2);

    // Update the screen
    SDL_RenderPresent(rend);
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, texture, NULL, NULL);

}
///======================================= X : khong,mot,hai,ba,bon,nam :
///                                            nhan vat thu X giu vien da nao do
///                                             nvmot , nvhai,... van the nhung o dang int
void run(SDL_Window *window,SDL_Renderer *renderer, State &s
            ,int nvkhong,int nvmot,int nvhai,int nvba,int nvbon,int nvnam){

    ///TIMELEFT
        unsigned int start = SDL_GetTicks();
        SDL_Rect srcRest;
        SDL_Rect desRectt;
        TTF_Font* font = NULL;

    ///---------------- 6 VIEN DA VO CUC -------------

    SDL_Surface * image0 = SDL_LoadBMP("0.bmp");
    SDL_Texture* texture_0 = SDL_CreateTextureFromSurface(renderer, image0);

    SDL_Surface * image1 = SDL_LoadBMP("1.bmp");
    SDL_Texture* texture_1 = SDL_CreateTextureFromSurface(renderer, image1);

    SDL_Surface * image2 = SDL_LoadBMP("2.bmp");
    SDL_Texture* texture_2 = SDL_CreateTextureFromSurface(renderer, image2);

    SDL_Surface * image3 = SDL_LoadBMP("3.bmp");
    SDL_Texture* texture_3 = SDL_CreateTextureFromSurface(renderer, image3);

    SDL_Surface * image4 = SDL_LoadBMP("4.bmp");
    SDL_Texture* texture_4 = SDL_CreateTextureFromSurface(renderer, image4);

    SDL_Surface * image5 = SDL_LoadBMP("5.bmp");
    SDL_Texture* texture_5 = SDL_CreateTextureFromSurface(renderer, image5);

    ///==================== AVENGERS =====================

    SDL_Surface * image = SDL_LoadBMP("background.bmp");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_Surface * plane = SDL_LoadBMP("thanos.bmp");
    SDL_Texture* texture_plane = SDL_CreateTextureFromSurface(renderer, plane);

    SDL_Surface * death = SDL_LoadBMP("death.bmp");
    SDL_Texture* texture_death = SDL_CreateTextureFromSurface(renderer, death);

    SDL_Surface * bullet = SDL_LoadBMP("bullet.bmp");
    SDL_Texture* texture_bullet = SDL_CreateTextureFromSurface(renderer, bullet);

    SDL_Surface * image00 = SDL_LoadBMP("00.bmp");
    SDL_Texture* texture_00 = SDL_CreateTextureFromSurface(renderer, image00);

    SDL_Surface * image11 = SDL_LoadBMP("11.bmp");
    SDL_Texture* texture_11 = SDL_CreateTextureFromSurface(renderer, image11);

    SDL_Surface * image22 = SDL_LoadBMP("22.bmp");
    SDL_Texture* texture_22 = SDL_CreateTextureFromSurface(renderer, image22);

    SDL_Surface * image33 = SDL_LoadBMP("33.bmp");
    SDL_Texture* texture_33 = SDL_CreateTextureFromSurface(renderer, image33);

    SDL_Surface * image44 = SDL_LoadBMP("44.bmp");
    SDL_Texture* texture_44 = SDL_CreateTextureFromSurface(renderer, image44);

    SDL_Surface * image55 = SDL_LoadBMP("55.bmp");
    SDL_Texture* texture_55 = SDL_CreateTextureFromSurface(renderer, image55);

    SDL_Surface * image66 = SDL_LoadBMP("66.bmp");
    SDL_Texture* texture_66 = SDL_CreateTextureFromSurface(renderer, image66);

    SDL_Surface * image77 = SDL_LoadBMP("77.bmp");
    SDL_Texture* texture_77 = SDL_CreateTextureFromSurface(renderer, image77);

    SDL_Surface * image88 = SDL_LoadBMP("88.bmp");
    SDL_Texture* texture_88 = SDL_CreateTextureFromSurface(renderer, image88);

    SDL_Surface * image99 = SDL_LoadBMP("99.bmp");
    SDL_Texture* texture_99 = SDL_CreateTextureFromSurface(renderer, image99);

    bool keep_running = true;
    while (keep_running){

        double dt =  0.01;///thoi gian di chuyen

        /// lenh dau vao
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                keep_running = false;
            else if (event.type == SDL_KEYDOWN) {
                switch ( event.key.keysym.sym ) {
                case SDLK_ESCAPE:
                    keep_running = false;
                    break;
                }
            }
        }

        const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
        /// sang phải
        if (keyboard_state[SDL_SCANCODE_RIGHT]&&s.PLAYER.b.x <= 800) {
            s.PLAYER.b.x += dt * 50.0;
        }
        /// sang trái
        if (keyboard_state[SDL_SCANCODE_LEFT]&&s.PLAYER.b.x >= 10) {
            s.PLAYER.b.x -= dt * 50.0;
        }
        /// len tren
        if (keyboard_state[SDL_SCANCODE_UP]&&s.PLAYER.b.y >= 10) {
            s.PLAYER.b.y -= dt * 50.0;
        }
        /// xuong duoi
        if (keyboard_state[SDL_SCANCODE_DOWN]&&s.PLAYER.b.y <= 700){
            s.PLAYER.b.y += dt * 50.0;
        }
        /// BẮN
        if (keyboard_state[SDL_SCANCODE_SPACE]) {
            s.bantrung = false;
            s.danban.x = s.PLAYER.b.x;
            s.danban.y = s.PLAYER.b.y ;
        }
        /// cập nhật trạng thái
        update_state(s);

        /// TIME LEFT
        if (TTF_Init() < 0)
        {
            SDL_Log("%s", TTF_GetError());
        }
        std::stringstream timeText;
        timeText << "" << 20 - ((SDL_GetTicks() - start)/1000 ) ;
        std::string text =  timeText.str();

        /// === IF YOU THUA ===================
        if(text == "0"||(s.quandich[nvkhong].chet&&s.quandich[nvmot].chet&&s.quandich[nvhai].chet&&s.quandich[nvba].chet&&s.quandich[nvbon].chet&&s.quandich[nvnam].chet)){
                    keep_running = false;
        }
        font = TTF_OpenFont("VeraMoBd.ttf", 100);
        ///------------------------------------
        SDL_Color fg = { 231, 76, 60 };
        SDL_Surface * surface_tl = TTF_RenderText_Solid(font, text.c_str(), fg);
        SDL_Texture* texture_tl = SDL_CreateTextureFromSurface(renderer, surface_tl);

        timeleft(renderer,texture_tl,font,srcRest,desRectt,text);

        /// === EVERYTHINGS CÒN LẠI =======================
        render(renderer,s,texture,texture_plane,texture_bullet
               ,texture_00,texture_11,texture_22,texture_33,texture_44,texture_55,texture_66,texture_77,texture_88,texture_99,texture_death
               ,nvkhong,nvmot,nvhai,nvba,nvbon,nvnam
               ,texture_0,texture_1,texture_2,texture_3,texture_4,texture_5);
        ///------------------------------------------------
    }
}


