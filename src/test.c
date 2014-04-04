/* hello.c - Gameboy Advance Tutorial - Loirak Development */
#define RGB16(r,g,b)  ((r)+(g<<5)+(b<<10)) 

#define REG_VCOUNT *(volatile unsigned short*)0x04000006
#define REG_KEYINPUT *(volatile int*)0x04000130
#define REG_SCREEN ((unsigned short*)0x6000000)

#define kSCREEN_WIDTH 240
#define kSCREEN_HEIGHT 160 

int m_x, m_y;

void vid_vsync_pre(void)
{
    while(REG_VCOUNT >= 160);   // wait till VDraw
}

void vid_vsync_post(void)
{
    while(REG_VCOUNT < 160);    // wait till VBlank
}

void clear(const int color)
{
  char x,y;
	// clear screen, and draw a blue back ground
	for(x = 0; x<240;x++)   //loop through all x
	{
		for(y = 0; y<160; y++)  //loop through all y
		{
			REG_SCREEN[x + y * kSCREEN_WIDTH] = color;
		}
	}
}

void square(int x, int y, int side, int color)
{
  char _x,_y;

	for(_x = (x > 0 ? x : 0); _x < x + side; ++_x)
		for(_y = (y > 0 ? y : 0); _y < y + side; ++_y)  
			REG_SCREEN[_x + _y * kSCREEN_WIDTH] = color;
}

void handle_keys(void)
{
  if (REG_KEYINPUT & (1 << 4))
    m_x -= 15;
  if (REG_KEYINPUT & (1 << 5))
    m_x += 15;
  if (REG_KEYINPUT & (1 << 6))
    m_y += 15;
  if (REG_KEYINPUT & (1 << 7))
    m_y -= 15;
}
int main(void)
{
  int bg = 0;
  int fg = RGB16(31,31,31); 
	*(unsigned long*)0x4000000 = 0x403; // set mode3, bg2 on 
  m_x = m_y = 0;

	while(1)
  {
    ++bg;
    vid_vsync_post();
    clear(bg);
    square(m_x, m_y, 20, RGB16(31,0,31));
    handle_keys();
    vid_vsync_pre();
  }	//loop forever
}
