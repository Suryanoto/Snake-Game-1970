#include "KOLEKSI_WINDOW.H"

void start(){
	switch(window_main()){
		case 2:
			window_Play();
		case 3:
			window_HS();
	}
}

int main(){
	fullscreen();
	start();
}




