/* hello.c - Gameboy Advance Tutorial - Loirak Development */

#include <cstddef>

#define kSCREEN_WIDTH 240
#define kSCREEN_HEIGHT 160 
#define RGB16(r,g,b) (r+(g<<5)+(b<<10))

template <typename T, size_t Address>
class MemoryMap
{
public:
    static void set(T value)
    {
        *(T*)Address = value;
    }

    static T& get()
    {
        return *(T*)Address;
    }

};

using RegVcount = MemoryMap<volatile unsigned short, 0x04000006>;
using RegKeyInput = MemoryMap<volatile int, 0x04000130>;
using RegScreen = MemoryMap<unsigned short, 0x6000000>;

int m_x, m_y;

int f_rgb(float fr, float fg, float fb)
{
  int r = (int)fr;
  int g = (int)fg;
  int b = (int)fb;
  return RGB16(r,g,b);
}

void vid_vsync_pre(void)
{
    while(RegVcount::get() >= 160);   // wait till VDraw
}

void vid_vsync_post(void)
{
    while(RegVcount::get() < 160);    // wait till VBlank
}

void clear(const int color)
{
	// clear screen, and draw a blue back ground
    for(size_t x = 0; x<240;x++)   //loop through all x
	{
        for(size_t y = 0; y<160; y++)  //loop through all y
		{
            (&RegScreen::get())[x + y * kSCREEN_WIDTH] = color;
		}
	}
}

void square(int x, int y, int side, int color)
{
  char _x,_y;

	for(_x = (x > 0 ? x : 0); _x < x + side; ++_x)
		for(_y = (y > 0 ? y : 0); _y < y + side; ++_y)  
			(&RegScreen::get())[_x + _y * kSCREEN_WIDTH] = color;
}

void handle_keys(void)
{
  const auto keys = RegKeyInput::get();
  if (keys & (1 << 4))
    m_x -= 15;
  if (keys & (1 << 5))
    m_x += 15;
  if (keys & (1 << 6))
    m_y += 15;
  if (keys & (1 << 7))
    m_y -= 15;
}


int main(void)
{
  float bgr = 0.f;
  float bgg = 0.f;
  float bgb = 0.f;


  int fg = RGB16(31,31,31); 
  MemoryMap<unsigned long, 0x4000000>::set(0x403);
	//*(unsigned long*)0x4000000 = 0x403; // set mode3, bg2 on 
  m_x = m_y = 0;

	while(1)
  {
    bgr += 0.1f;
    bgg += 0.2f;
    bgb += 0.3f;
    vid_vsync_post();
    clear(f_rgb(bgr, bgg, bgb));
    square(m_x, m_y, 20, RGB16(0,31,31));
    handle_keys();
    vid_vsync_pre();
  }	//loop forever
}
