#include <stdio.h>
#include <time.h>

//#if defined(__CYGWIN__)
#include <errno.h>
//#endif

/*
 * Except for the point size all units in this program are tenths of
 * points whith 72 points per inch.
 */

#define PAGE_HEIGHT		(1166 * 72 / 10)	/* 11.66" */
#define PAGE_WIDTH		(825 * 72 /10)		/* 8.25" */
#define TOP_MARGIN		630	/* to get 66 lines with defaults */
#define BOTTOM_MARGIN		630	/* to get 66 lines with defaults */
#define LEFT_MARGIN		590	/* to get 66 lines with -r -c2 -p6 */
#define RIGHT_MARGIN		590	/* to get 66 lines with -r -c2 -p6 */
#define GAP			630
#define YILS			12	/* vs = ps * yils / 10 */
#define DEFAULT_FONT		"Courier"
#define DEFAULT_POINT_SIZE	9
#define DEFAULT_ROTATE		0	/* either 0 or 1 */
#define DEFAULT_COLUMNS		1
#define DEFAULT_COPIES		1
#define DEFAULT_LINES		0	/* 0 means as many as will fit */
#define DEFAULT_VERTICAL_SPACE	0	/* 0 means vs = YILS * ps / 10 */
#define DEFAULT_BREAK		1	/* new file on new page */
#define DEFAULT_TITLE		((char *) 0)
#define DEFAULT_TITLE_FONT	"Helvetica"
#define DEFAULT_TITLE_PS	12
#define DEFAULT_TITLE_X		0
#define DEFAULT_TITLE_Y		0
#define DEFAULT_PRINT_FILE_NAME	0
#define DEFAULT_BORDER		0
#define DEFAULT_TAB_WIDTH	8

int rotate = DEFAULT_ROTATE;		/* 0 = portrait, 1 = landscape */
int nbr_cols = DEFAULT_COLUMNS;		/* # of columns */
int lines = DEFAULT_LINES;		/* # of lines; 0: as many as will fit */
char *font_name = DEFAULT_FONT;		/* the font */
int point_size = DEFAULT_POINT_SIZE;	/* the point size */
int vert_space = DEFAULT_VERTICAL_SPACE;/* 10 * points between lines */
int nbr_copies = DEFAULT_COPIES;	/* # of copies */
int page_width = PAGE_WIDTH;
int page_height = PAGE_HEIGHT;
int left_margin = LEFT_MARGIN;
int right_margin = RIGHT_MARGIN;
int top_margin = TOP_MARGIN;
int bottom_margin = BOTTOM_MARGIN;
int always_break = DEFAULT_BREAK;
char *current_file;
char *title = DEFAULT_TITLE;
char *title_font = DEFAULT_TITLE_FONT;
int title_ps = DEFAULT_TITLE_PS;
int title_x = DEFAULT_TITLE_X;
int title_y = DEFAULT_TITLE_Y;
int print_file_name = DEFAULT_PRINT_FILE_NAME;
int gap = GAP;
int border = DEFAULT_BORDER;		/* border type */
int tab_width = DEFAULT_TAB_WIDTH;	/* width of TABs */
int page_nbr;				/* current page number */
int file_page;				/* current page of current file */
int col_nbr;				/* current column */
int yils;				/* 10 * interline spacing */
char *cmd_name;				/* name by which program was called */
int had_option;
int col_width;
int in_page;
int xpos, ypos;
int linectr;
int left_edge, right_edge, top_edge, bottom_edge;
int done_header;
int force_break;
int current_font;

/* possible values of current_font */
#define NO_FONT			0
#define TEXT_FONT		1
#define TITLE_FONT		2

struct fonts {
	char *font_name;
	struct fonts *font_next;
} *fonts;

extern FILE *fopen();
extern char *malloc();
extern char *asctime();
/* extern struct tm *localtime(); */
/* extern long time(); */
extern double atof();
#if !defined(__CYGWIN__)
extern int errno;
#endif

do_option(argv, argc, argp)
char **argv;
int *argp;
{
	int c, n;

	switch (argv[*argp][1]) {
	case '1':			/* one column mode */
		nbr_cols = 1;
		font_name = "Courier";
		point_size = 9;
		vert_space = 0;
		rotate = 0;
		lines = 0;
		top_margin = 630;
		bottom_margin = 630;
		left_margin = 590;
		right_margin = 590;
		had_option = 1;
		force_break = 1;
		break;
	case '2':			/* two column mode */
		nbr_cols = 2;
		font_name = "Courier";
		point_size = 6;
		vert_space = 0;
		rotate = 1;
		lines = 0;
		top_margin = 630;
		bottom_margin = 630;
		left_margin = 590;
		right_margin = 590;
		gap = 630;
		had_option = 1;
		force_break = 1;
		break;
	case 'l':			/* # of lines */
		if (argv[*argp][2])
			lines = atoi(&argv[*argp][2]);
		else if (++*argp < argc)
			lines = atoi(argv[*argp]);
		else
			usage();
		if (lines < 0)
			lines = 0;
		break;
	case '#':			/* # of copies */
		if (argv[*argp][2])
			nbr_copies = atoi(&argv[*argp][2]);
		else if (++*argp < argc)
			nbr_copies = atoi(argv[*argp]);
		else
			usage();
		if (nbr_copies <= 0)
			usage();
		force_break = 1;
		break;
	case 'c':			/* # of columns */
		if (argv[*argp][2])
			nbr_cols = atoi(&argv[*argp][2]);
		else if (++*argp < argc)
			nbr_cols = atoi(argv[*argp]);
		else
			usage();
		if (nbr_cols <= 0)
			usage();
		force_break = 1;
		break;
	case 'f':			/* font */
		if (argv[*argp][2])
			font_name = &argv[*argp][2];
		else if (++*argp < argc)
			font_name = argv[*argp];
		else
			usage();
		break;
	case 'p':			/* point size */
		if (argv[*argp][2])
			point_size = atoi(&argv[*argp][2]);
		else if (++*argp < argc)
			point_size = atoi(argv[*argp]);
		else
			usage();
		if (point_size <= 0)
			usage();
		break;
	case 'v':			/* vertical spacing */
		if (argv[*argp][2])
			vert_space =
				(int) (atof(&argv[*argp][2])*10.);
		else if (++*argp < argc)
			vert_space =
				(int) (atof(argv[*argp]) * 10.);
		else
			usage();
		if (vert_space < 0)
			usage();
		break;
	case 'r':			/* orientation */
		if ((c = argv[*argp][2]) == 0) {
			if (++*argp < argc)
				c = argv[*argp][0];
			else
				usage();
		}
		switch (c) {
		case 'p': rotate = 0; break;		/* portrait */
		case 'l': rotate = 1; break;		/* landscape */
		default:  usage();
		}
		force_break = 1;
		break;
	case 'b':			/* force page break */
		if ((c = argv[*argp][2]) == 0) {
			if (++*argp < argc)
				c = argv[*argp][0];
			else
				usage();
		}
		switch (c) {
		case '+': always_break = 1; break;
		case '-': always_break = 0; break;
		default:  usage();
		}
		break;
	case 'm':			/* set margin */
		if ((c = argv[*argp][2]) == 0)
			usage();
		if (argv[*argp][3])
			n = (int) (atof(&argv[*argp][3]) * 10.);
		else if (++*argp < argc)
			n = (int) (atof(argv[*argp]) * 10.);
		else
			usage();
		if (n < 0)
			usage();
		switch (c) {
		case 't': top_margin = n; break;
		case 'b': bottom_margin = n; break;
		case 'l': left_margin = n; break;
		case 'r': right_margin = n; break;
		case 'g': gap = n; break;
		default:  usage();
		}
		break;
	case 't':			/* print title */
		if ((c = argv[*argp][2]) == 0) {
			if (++*argp < argc)
				c = argv[*argp][0];
			else
				usage();
		}
		switch (c) {
		case '+': print_file_name = 1; always_break = 1; break;
		case '-': print_file_name = 0; break;
		default:  usage();
		}
		title = 0;
		break;
	case 'T':			/* specify title */
		if (argv[*argp][2])
			title = &argv[*argp][2];
		else if (++*argp < argc)
			title = argv[*argp];
		else
			usage();
		print_file_name = 0;
		force_break = 1;
		break;
	case 'F':			/* title font */
		if (argv[*argp][2])
			title_font = &argv[*argp][2];
		else if (++*argp < argc)
			title_font = argv[*argp];
		else
			usage();
		break;
	case 'P':			/* title point size */
		if (argv[*argp][2])
			title_ps = atoi(&argv[*argp][2]);
		else if (++*argp < argc)
			title_ps = atoi(argv[*argp]);
		else
			usage();
		if (point_size <= 0)
			usage();
		break;
	case 'B':			/* border type */
		if (argv[*argp][2])
			border = atoi(&argv[*argp][2]);
		else if (++*argp < argc)
			border = atoi(argv[*argp]);
		else
			usage();
		if (border < 0 || border > 0xFF)
			usage();
		break;
	case 'w':			/* tab width */
		if (argv[*argp][2])
			tab_width = atoi(&argv[*argp][2]);
		else if (++*argp < argc)
			tab_width = atoi(argv[*argp]);
		else
			usage();
		if (tab_width <= 0)
			usage();
		break;
	default:
		usage();
	}
}

main(argc, argv)
char **argv;
{
	int arg;
	int done_file = 0;
	FILE *f;
	int errors;

	cmd_name = argv[0];
	for (arg = 1; arg < argc; arg++) {
		if (argv[arg][0] == '-') {
			if (argv[arg][1] == 0) {
				done_file = 1;
				current_file = 0;
				print_file(stdin);
				continue;
			}
			do_option(argv, argc, &arg);
			had_option = 1;
			continue;
		}
		done_file = 1;
		if ((f = fopen(argv[arg], "r")) == 0) {
			fprintf(stderr, "%s: %s: %s\n", cmd_name, argv[arg],
				strerror(errno));
			errors++;
			continue;
		}
		current_file = argv[arg];
		print_file(f);
		fclose(f);
	}
	if (!done_file) {
		current_file = 0;
		print_file(stdin);
	}
	if (in_page)
		finish_page();
	if (done_header) {
		struct fonts *fnt;

		printf("%%%%Trailer\n");
		printf("%%%%DocumentFonts:");
		for (fnt = fonts; fnt; fnt = fnt->font_next)
			printf(" %s", fnt->font_name);
		printf("\n");
		printf("%%%%Pages: %d\n", page_nbr);
	}
	exit(errors);
}

print_file(f)
FILE *f;
{
	int i;
	register int c, outcol = 0;
	time_t the_time;

	file_page = 0;
	if (!done_header) {
		done_header = 1;
		printf("%%!PS-Adobe-1.0\n");
		printf("%%%%Creator: The program '%s'\n", cmd_name);
		(void) time(&the_time);
		printf("%%%%CreationDate: %s", asctime(localtime(&the_time)));
		printf("%%%%Title: File listing\n");
		printf("%%%%Pages: (atend)\n");
		printf("%%%%DocumentFonts: (atend)\n");
		printf("%%%%EndComments\n\n");
		printf("/nl {xline yline moveto show /yline yline yils sub def /xline colstart def} bind def\n");
		printf("/bs {xline yline moveto dup show stringwidth pop xline add sw sub /xline exch def} bind def\n");
		printf("/title {dup stringwidth pop 4 -1 roll exch sub 3 -1 roll moveto show } bind def\n");
		printf("%%%%EndProlog\n\n");
		had_option = 1;
	}
	if (in_page && (print_file_name || always_break || force_break))
		finish_page();
	force_break = 0;
	if (had_option) {
		register struct fonts **fnt;

		printf("/textfont /%s findfont %d scalefont def\n", font_name,
			point_size);
		current_font = NO_FONT;
		for (fnt = &fonts; *fnt; fnt = &(*fnt)->font_next)
			if (strcmp((*fnt)->font_name, font_name) == 0)
				break;
		if (*fnt == 0) {
			*fnt = (struct fonts *) malloc(sizeof(struct fonts));
			(*fnt)->font_name = font_name;
			(*fnt)->font_next = 0;
		}
		if (vert_space)
			yils = vert_space;
		else
			yils = point_size * YILS;
		printf("/yils %.1f def\n", (double) yils / 10.);
		if (rotate) {
			if (lines) {
				top_edge = - (page_width - lines*yils) / 2;
				bottom_edge = -page_width - top_edge;
			} else {
				bottom_edge = -page_width + right_margin;
				top_edge = -left_margin;
			}
			left_edge = bottom_margin;
			right_edge = page_height - top_margin;
		} else {
			if (lines) {
				bottom_edge = (page_height - lines*yils) / 2;
				top_edge = page_height - bottom_edge;
			} else {
				bottom_edge = bottom_margin;
				top_edge = page_height - top_margin;
			}
			left_edge = left_margin;
			right_edge = page_width - right_margin;
		}
		col_width = (right_edge - left_edge - (nbr_cols - 1) * gap)
				/ nbr_cols;
		for (i = 0; i < nbr_cols; i++) {
			int left, right;

			printf("/clippath%d { newpath ", i);
			left = left_edge + i * (col_width + gap);
			right = left + col_width;
			printf("%.1f 999 moveto %.1f -999 lineto ",
				(double) left / 10., (double) left / 10.);
			printf("%.1f -999 lineto %.1f 999 lineto ",
				(double) right / 10., (double) right / 10.);
			printf("closepath } def\n");
		}
		printf("/#copies %d def\n", nbr_copies);
		had_option = 0;
	}
	if (!in_page)
		start_page();
	start_column();
	printf("(");
	while ((c = getc(f)) != EOF) {
		switch (c) {
		case '\f':
			/* force a new column */
			ypos = bottom_edge;
			linectr = lines-1;
			if ((c = getc(f)) != '\n' && c != EOF)	/* skip LF */
				ungetc(c, f);
			/* fall through */
		case '\n':
			printf(") nl\n");
			outcol = 0;
			ypos -= yils;
			linectr++;
			if ((c = getc(f)) == EOF) {
				finish_column();
				return;
			}
			ungetc(c, f);
			if (lines == 0 ? ypos <= bottom_edge : linectr == lines) {
				finish_column();
				if (!in_page)
					start_page();
				start_column();
			}
			printf("(");
			break;
		case '\t':
			do
				putchar(' ');
			while (++outcol % tab_width);
			break;
		case '\b':
			printf(") bs (");
			outcol--;
			break;
		case '\\':
		case '(':
		case ')':
			putchar('\\');
			/* fall through */
		default:
			if (c >= 0177)
				printf("\\%03o", c);
			else
				putchar(c);
			outcol++;
			break;
		}
	}
	/* come here only if last character of file is not linefeed */
	printf(") nl\n");
	finish_column();
}

finish_page()
{
	int i;

	printf("showpage\n");
	in_page = 0;
}

start_page()
{
	page_nbr++;
	file_page++;
	printf("%%%%Page: %d %d\n", file_page, page_nbr);
	col_nbr = 0;
	in_page = 1;
	draw_border();
	draw_title();
}

start_column()
{
	xpos = left_edge + (col_width + gap) * col_nbr;
	ypos = top_edge - yils / 2;	/* make room for first line */
	linectr = 0;
	if (current_font != TEXT_FONT) {
		printf("textfont setfont\n");
		current_font = TEXT_FONT;
		printf("/sw ( ) stringwidth pop def\n");
	}
	printf("gsave\n");
	if (rotate)
		printf("90 rotate\n");
	printf("/yline %.1f def\n", (double) ypos / 10.);
	printf("/xline %.1f def\n", (double) xpos / 10.);
	printf("/colstart %.1f def\n", (double) xpos / 10.);
	printf("clippath%d clip\n", col_nbr);
}

finish_column()
{
	printf("grestore\n");
	if (++col_nbr >= nbr_cols)
		finish_page();
}

draw_border()
{
	int tx1, ty1, tx2, ty2;
	register int i;
	static char line[] = "lineto";
	static char move[] = "moveto";

	if (!border)
		return;
	
	printf("gsave\n");
	if (rotate) {
		printf("90 rotate\n");
		tx1 = left_edge - bottom_margin/2;
		ty1 = top_edge + left_margin/2;
		tx2 = right_edge + top_margin/2;
		ty2 = bottom_edge - right_margin/2;
	} else {
		tx1 = left_edge - left_margin/2;
		ty1 = top_edge + top_margin/2;
		tx2 = right_edge + right_margin/2;
		ty2 = bottom_edge - bottom_margin/2;
	}
	if (border & 0xF) {
		printf("%.1f %.1f moveto\n",
			(double) tx1 / 10., (double) ty1 / 10.);
		printf("%.1f %.1f %s\n",
			(double) tx1 / 10., (double) ty2 / 10.,
			border & 0x01 ? line : move);
		printf("%.1f %.1f %s\n",
			(double) tx2 / 10., (double) ty2 / 10.,
			border & 0x02 ? line : move);
		printf("%.1f %.1f %s\n",
			(double) tx2 / 10., (double) ty1 / 10.,
			border & 0x04 ? line : move);
		printf("%.1f %.1f %s\n",
			(double) tx1 / 10., (double) ty1 / 10.,
			border & 0x08 ? line : move);
	}
	if (border & 0x70) {
		for (i = 1; i < nbr_cols; i++) {
			tx1 = left_edge + (col_width + gap) * i - gap/2;
			if (border & 0x20)
				printf("%.1f %.1f moveto %.1f %.1f lineto\n",
					(double) tx1 / 10., (double) ty1 / 10.,
					(double) tx1 / 10., (double) top_edge / 10.);
			if (border & 0x10)
				printf("%.1f %.1f moveto %.1f %.1f lineto\n",
					(double) tx1 / 10., (double) top_edge / 10.,
					(double) tx1 / 10., (double) bottom_edge / 10.);
			if (border & 0x40)
				printf("%.1f %.1f moveto %.1f %.1f lineto\n",
					(double) tx1 / 10., (double) ty2 / 10.,
					(double) tx1 / 10., (double) bottom_edge / 10.);
		}
	}
	printf("stroke\ngrestore\n");
}

draw_title()
{
	register int set_font = 0;
	register struct fonts **fnt;
	register char *t;
	register int tx;

	if ((t = title) == 0 && (!print_file_name || (t = current_file) == 0))
		return;
	tx = (rotate ? right_edge : top_edge) + top_margin/2 + 50;
	printf("gsave\n");
	if (title_ps != point_size || strcmp(title_font, font_name) != 0) {
		current_font = TITLE_FONT;
		printf("/%s findfont %d scalefont setfont\n", title_font,
			title_ps);
		for (fnt = &fonts; *fnt; fnt = &(*fnt)->font_next)
			if (strcmp((*fnt)->font_name, title_font) == 0)
				break;
		if (*fnt == 0) {
			*fnt = (struct fonts *) malloc(sizeof(struct fonts));
			(*fnt)->font_name = title_font;
			(*fnt)->font_next = 0;
		}
	}
	printf("%.1f %.1f (",
		title_x ? (double)title_x/10. : (page_width-right_margin)/10.,
		title_y ? (double)title_y/10. : (double) tx / 10.);
	while (*t) {
		if (*t == '(' || *t == ')' || *t == '\\')
			putchar('\\');
		putchar(*t);
		t++;
	}
	printf(") title\ngrestore\n");
}

usage()
{
	fprintf(stderr, "Usage: %s [options] [files]\n", cmd_name);
	fprintf(stderr, "Options and files can be intermixed;\n");
	fprintf(stderr, "they are valid for all following files until overriden.\n");
	fprintf(stderr, "\t-1\t\tOne column, 9 points Courier, portrait\n");
	fprintf(stderr, "\t-2\t\tTwo columns, 6 points Courier, landscape\n");
	fprintf(stderr, "\t-w n\t\twidth of TAB characters\n");
	fprintf(stderr, "\t-l n\t\t# of lines\n");
	fprintf(stderr, "\t-# n\t\t# of copies\n");
	fprintf(stderr, "\t-c n\t\t# of columns\n");
	fprintf(stderr, "\t-f font\t\tfont\n");
	fprintf(stderr, "\t-p n\t\tpoint size\n");
	fprintf(stderr, "\t-v n\t\tvertical spacing (n = 0: vs = 1.2 * ps)\n");
	fprintf(stderr, "\t-r [l|p]\torientation (l: landscape; p: portrait)\n");
	fprintf(stderr, "\t-b [+|-]\tnew file on new page (+: switch on; -: switch off)\n");
	fprintf(stderr, "\t-mt n\t\ttop margin\n");
	fprintf(stderr, "\t-mb n\t\tbottom margin\n");
	fprintf(stderr, "\t-ml n\t\tleft margin\n");
	fprintf(stderr, "\t-mr n\t\tright margin\n");
	fprintf(stderr, "\t-mg n\t\tinter-column gap\n");
	fprintf(stderr, "\t-t [+|-]\tprint file name as title (+: switch on; -: switch off)\n");
	fprintf(stderr, "\t-T text\t\tprint text as title\n");
	fprintf(stderr, "\t-F font\t\ttitle font\n");
	fprintf(stderr, "\t-P n\t\ttitle point size\n");
	fprintf(stderr, "\t-B n\t\tdraw border type n\n");
	fprintf(stderr, "\t\t\t\tn =  1 left border\n");
	fprintf(stderr, "\t\t\t\tn =  2 top border\n");
	fprintf(stderr, "\t\t\t\tn =  4 right border\n");
	fprintf(stderr, "\t\t\t\tn =  8 bottom border\n");
	fprintf(stderr, "\t\t\t\tn = 16 middle line\n");
	fprintf(stderr, "\t\t\t\tn = 32 middle line to top\n");
	fprintf(stderr, "\t\t\t\tn = 64 middle line to bottom\n");
	fprintf(stderr, "\t\t\t\tthese numbers can be added together\n");
	exit(1);
}
