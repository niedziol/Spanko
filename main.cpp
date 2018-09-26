#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "object.h"
#include "square_object.h"

enum KEYS{UP, DOWN, LEFT, RIGHT};
bool keys[4];

class Player : public Object{
    protected:
        int length = 20;
        //int speed = 5;
    public:
        Player (int x, int y){
            this -> x = x;
            this -> y = y;
            al_draw_filled_rectangle(this -> x, this -> y, this -> x + this -> length, this -> y + this -> length, al_map_rgb(255, 255, 255));
        }

        void update(){
            al_draw_filled_rectangle(this -> x, this -> y, this -> x + this -> length, this -> y + this -> length, al_map_rgb(255, 255, 255));
        }
};

void must_init(bool test, const char *desc){
    if (test) return;
    
    printf("couldn't initialize %s\n", desc);
    exit(-1);
}

int main(int argc, char **argv){

    //initialize allegro
    must_init(al_init(), "allegro");

    //install keyboard
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_KEYBOARD_STATE keyboard;

    //create display
    ALLEGRO_DISPLAY* display = nullptr;

    display = al_create_display(960, 540);
    al_set_window_title(display, "Check Window");
    must_init(display, "display");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    must_init(al_init_primitives_addon(), "primitives");
    
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    Player player(0,0);
    
    int speed = 5;
    bool redraw = true;
    bool done = false;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    SquareObstacle * test = new SquareObstacle(600, 400, 30);
    

    while(!done){
        al_wait_for_event(queue, &event);
        switch(event.type){
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                if (keys[UP]){
                    player.move(0, -speed);
                }
                if (keys[DOWN]){
                    player.move(0, speed);
                }
                if (keys[LEFT]){
                    player.move(-speed, 0);
                }
                if (keys[RIGHT]){
                    player.move(speed, 0);
                }
                
                test -> move(-1, 0);
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch(event.keyboard.keycode){
                    case ALLEGRO_KEY_UP:
                        keys[UP] = true;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        keys[DOWN] = true;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        keys[LEFT] = true;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        keys[RIGHT] = true;
                        break;
                }
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch(event.keyboard.keycode){
                    case ALLEGRO_KEY_UP:
                        keys[UP] = false;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        keys[DOWN] = false;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        keys[LEFT] = false;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        keys[RIGHT] = false;
                        break;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    done = true;
                break;
        }
        if (done)
            break;
        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            player.update();
            test -> update();
            al_flip_display();
            redraw = false;
        }
    }


    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}