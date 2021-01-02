Floyd-Steinberg dithering:
	for each pixel:
		t = true colour
		p = closes palette colour
		e = quantisation error: t - p
		modify colours of neighbours from east to south-west based on error

For a linear gradient (assuming vertical, for example), we can consider each row independently based on how far it is between endpoints A and B. We can scan horizontally and place a certain number of pixels to be either colour a or colour b, depending on the proportion.

If the distance between A and B is n pixels, the ratio of pixels coloured a vs. coloured b goes from 0/n to n/n.

Alternatively, we use a number of pre-set fills (eg. left to right):

0/8    1/8    2/8    3/8    4/8    5/8    6/8    7/8    8/8
xxxxxx xx.xxx xxx.xx xx.xx. x.x.x. ..x..x ...x.. ..x... ......
xxxxxx xxxxxx x.xxx. x.x.xx .x.x.x .x.x.. .x...x ...... ......
xxxxxx .xxxxx .xxx.x .xx.x. x.x.x. x..x.x x...x. x..... ......
xxxxxx xxxx.x xx.xxx x.xx.x .x.x.x .x..x. ..x... ....x. ......

Fractions denote how many of each 8 values (read per-column left to right) are each colour.
