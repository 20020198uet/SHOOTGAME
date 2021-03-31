#include "ingame.h"
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
///-----------------------------------------------
void render(SDL_Renderer *rend, State &s,int coloring) {
    SDL_SetRenderDrawColor(rend, 0, 70, 130, 255);
    SDL_RenderClear(rend);///tach dan ban khoi keo dai

    /// Quan dich
    for(int i = 0; i < s.N; i++){
        if (s.quandich[i].song){
            if (s.quandich[i].chet){
                srand(0);
                draw_block(rend, s.quandich[i].b, rand(), 0, 0, 255);
            }
            else
                draw_block(rend, s.quandich[i].b, 0, 255, 0, 0);
        }
    }


    /// Player
    if(coloring == 0) draw_block(rend, s.PLAYER.b, 0, 153 , 255 , 255);

    else draw_block(rend, s.PLAYER.b, 254 , 6 , 145 ,255);

    /// Bullet
    draw_block(rend, s.danban, 255, 255, 0, 0);

    /// Stage number
    for (int i = 0; i < s.stage+1; i++) {
        SDL_Rect r = {(i+1)*10, 10, 5, 5};
        SDL_SetRenderDrawColor(rend, 240, 170, 0, 200);
        SDL_RenderFillRect(rend, &r);
    }

    // Update the screen
    SDL_RenderPresent(rend);
}
///------------------------------
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

    s.stage = stage;

    /// Enemies
    for (int i = 0; i < s.N; i++) {
        s.quandich[i].song = false;
    }

    int enemy_size = 20;
    int ww = 8; // so quan dich hang ngang
    int hh = 2; // so quan dich hang doc
    for(int i = 0 ;i < ww; ++i)
    for(int j = 0;j < hh; ++j){
                int index = i + j*ww;
                s.quandich[index].song = true;
                s.quandich[index].chet = false;
                s.quandich[index].b.x =  i*60 + 100;
                s.quandich[index].b.y =  j*60 + 100;

                ///rand kích thc sau mỗi level
                int size = enemy_size - (rand()%(stage + 1));
                if (size < enemy_size / 2) size = enemy_size / 2;
                s.quandich[index].b.size = size;
    }
}
/// hàm kiểm tra chạm nhau
bool collide(const Block &b1, const Block &b2) {
    return
        (abs(b1.x - b2.x) < b1.size + b2.size) && (abs(b1.y - b2.y) < b1.size + b2.size);
}

///---------------------------------------------
void update_state(State &s, double dt) {
    /// đạn bắn
    if (!s.bantrung) {
        s.danban.y -= 200.0 * dt;
        if (s.danban.y < 0) {
            s.bantrung = true;
            s.danban.y = s.h*2;
        }
    }

    /// di chuyển quân địch - crazy movement
    s.global_time += dt;
    double t = s.global_time;
    double speed = (18.0 + 2.0 * s.stage) * sqrt(t);
    double freq = 6.0 + s.stage/4;
    double z = 2.0 * sin(freq * t) + pow(sin(0.25 * freq * t),19);

    double displace_x = speed * z * dt;
    double displace_y = 0.03 * speed * pow(z,4) * dt;

    bool player_died = false;
    bool enemies_are_dead = true;

    for (int i=0; i < s.N; i++) {
        if (s.quandich[i].song) {

            if (s.quandich[i].chet) {
                /// ban chet quan dich
                s.quandich[i].b.y += 0.5 ;

            }


            /// neu trung dan
            if ( collide (s.quandich[i].b, s.danban) ) {
                if ( !s.quandich[i].chet ){
                    s.quandich[i].chet = true;

                }
                s.bantrung = true;
                s.danban.y = s.h*2;//dan bien mat
            }
            enemies_are_dead = false;

        }
    }

    if (player_died) {
        int prev_stage = s.stage-1;
        if (prev_stage < 0) prev_stage = 0;
        init_state(s, prev_stage);
    }

    if (enemies_are_dead) {
        int x = s.PLAYER.b.x;
        init_state(s, s.stage + 1);
        s.PLAYER.b.x = x;
    }

}
///-----------------------------------------------
void run(SDL_Renderer *renderer, State &s, int x ) {

    bool keep_running = true;
    while (keep_running) {

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
            s.PLAYER.b.x += dt * 100.0;
        }
        /// sang trái
        if (keyboard_state[SDL_SCANCODE_LEFT]&&s.PLAYER.b.x >= 10) {
            s.PLAYER.b.x -= dt * 100.0;
        }
        /// len tren
        if (keyboard_state[SDL_SCANCODE_UP]) {
            s.PLAYER.b.y -= dt * 200.0;
        }
        /// xuong duoi
        if (keyboard_state[SDL_SCANCODE_DOWN]) {
            s.PLAYER.b.y += dt * 200.0;
        }
        /// BẮN
        if (keyboard_state[SDL_SCANCODE_SPACE]) {
            s.bantrung = false;
            s.danban.x = s.PLAYER.b.x;
            s.danban.y = s.PLAYER.b.y - s.PLAYER.b.size;
        }

        /// cập nhật trạng thái
        update_state(s, dt);

        /// vẽ
        render(renderer, s,x);

        SDL_Delay(2);

    }
}


