#include <iostream>  
#include <stdexcept>  
  
class Game {  
  public:  
    Game(int x, int y): h(x), p(y), count_h(0), count_p(0),  
                        heaps(new int[x]), players(new Player*[y]) {}  
    ~Game (){  
      delete [] heaps;  
      delete [] players;  
    }  
  
    void addHeap(int coins) throw(std::logic_error){  
      if (coins<=0 || count_h>=h) throw std::logic_error("invalid heap");  
      heaps[count_h]=coins;  
      count_h++;  
    }  
    void addPlayer(Player *player) throw(std::logic_error){  
      if (count_p>=p) throw std::logic_error("invalid player");  
      players[count_p]=player;  
      count_p++;  
    }  
    void play(std::ostream &out) throw(std::logic_error){  
      if (h!=h_count || p!=p_count) throw std::logic_error("invalid game");
      State s(h, heaps);  
      int i=0;  
      while (!s.winning()){  
        out<<"State: "<<s<<endl;  
        out<<*players[i%p]<<" "<<players[i%p]->play(s)<<endl;  
        s.next(players[i%p]->play(s));  
        i++;  
      }  
      out<<"State: "<<s<<endl;  
      out<<*players[(i-1)%p]<<" wins"<<endl;  
    }  
  
  private:  
    int h, p, count_h, count_p, *heaps;  
    Player **players;  
}; 
