#include "camera.h"
#include <wiringPi.h>

Camera::Camera(int parameter)
{
	if(parameter==0)
	{
		system("raspivid -t 0 -n --width 1280 --height 720 -o - | cvlc stream:///dev/stdin --sout '#standard{access=http,mux=ts,dst=:8090}' :demux=h264");
	}
	if(parameter==1)
	{	
		system("raspistill --nopreview -w 640 -h 480 -q 5 -o /tmp/stream/pic.jpg -tl 500 -t 9999999 &");
        //delay(100);
        system("LD_LIBRARY_PATH=/usr/local/lib mjpg_streamer -i \"input_file.so -f /tmp/stream -n pic.jpg\" -o \"output_http.so -w ./www\" &");
	}
}

Camera::~Camera()
{
	system("killall vlc");
	system("killall raspivid");
}
