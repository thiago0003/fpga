/*
 * Source: https://rosettacode.org/wiki/Conway%27s_Game_of_Life#C
 * Change log: changing resolution again and changing variables to registers 
 */
#define h 30
#define w 40

#define for_x for (register int x = 0; x < w; x++)
#define for_y for (register int y = 0; y < h; y++)

#define _idx(x,y) ((((x)<<6) + ((x)<<4)) + (y)) // for 40

unsigned char univ[h*w];
unsigned char b1[w], b2[w], tail[w], head[w];

void main()
{
    register unsigned char n;
	// prologue
    while (1) {
        for_x {
            head[x] = univ[_idx(0, x)]; 
            tail[x] = univ[_idx(h-1, x)]; 
        }
        // kernel
        for (register int y = 0; y < h-1; y++) { 
            for_x {
                n = tail          [x ? x-1 : w-1 ] + tail     [x]      + tail          [x==w-1 ? 0 : x+1 ] +
                    univ[_idx(y  , x ? x-1 : w-1)] +                     univ[_idx(y  , x==w-1 ? 0 : x+1)] +
                    univ[_idx(y+1, x ? x-1 : w-1)] + univ[_idx(y+1,x)] + univ[_idx(y+1, x==w-1 ? 0 : x+1)]; 
                b1[x] = ((n | univ[_idx(y,x)]) == 3);
            }
            for_x {
                tail[x] = univ[_idx(y,x)];
                if (y > 0) 
                    univ[_idx(y-1, x)] = b2[x];
                b2[x] = b1[x];
            }
        }
        // epilogue
        for_x {
            n = tail     [x ? x-1 : w-1] + tail   [x] + tail     [x==w-1 ? 0 : x+1] +
                univ[_idx(h-1, x ? x-1 : w-1)] +              univ[_idx(h-1, x==w-1 ? 0 : x+1)] +
                head     [x ? x-1 : w-1] + head   [x] + head     [x==w-1 ? 0 : x+1]; 
            b2[x] = ((n | univ[_idx(h-1, x)]) == 3);
        }
        for_x {
            univ[_idx(h-2, x)] = b1[x];
            univ[_idx(h-1, x)] = b2[x];
        }
    }
    return;
}
