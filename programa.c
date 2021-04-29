#include <gtk/gtk.h>
#include <math.h>

//https://developer.gnome.org/gtk3/stable/gtk-getting-started.html#id-1.2.3.5
static void carregarImagem(GtkWidget *widget, gpointer app)
{
	GtkWidget *imgOriginal = g_object_get_data(G_OBJECT(app), "Original");
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GtkWidget *arq = g_object_get_data(G_OBJECT(app), "Caminho");
	const gchar *arqPath = gtk_entry_get_text(GTK_ENTRY(arq));
	
	gtk_image_set_from_file(GTK_IMAGE(imgOriginal), arqPath);
	gtk_image_set_from_file(GTK_IMAGE(imgAlterada), arqPath);	
}

static void recuperarOriginal(GtkWidget *widget, gpointer app)
{
	GtkWidget *imgOriginal = g_object_get_data(G_OBJECT(app), "Original");
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	
	
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgOriginal));
	GdkPixbuf *bufRecuperado= gdk_pixbuf_copy(bufOriginal);
	GdkPixbuf *bufDeleter = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufRecuperado);
	g_object_unref(bufDeleter);
}

static void espelharH(GtkWidget *widget, gpointer app)
{
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	GdkPixbuf *bufAlterada = gdk_pixbuf_copy(bufOriginal);
	
	int width, height, rowstride, n_channels;
	guchar *pixelsO, *pixelsA, *pa, *po;

	width = gdk_pixbuf_get_width (bufOriginal);
	height = gdk_pixbuf_get_height (bufOriginal);
	rowstride = gdk_pixbuf_get_rowstride(bufOriginal);
	pixelsO = gdk_pixbuf_get_pixels(bufOriginal);
	pixelsA = gdk_pixbuf_get_pixels(bufAlterada);
	n_channels = gdk_pixbuf_get_n_channels(bufOriginal);
	
	g_print("width: %d \n", width);
	g_print("height: %d \n", height);
	g_print("rowstride: %d \n", rowstride);
	g_print("pixels: %p \n", pixelsA);
	g_print("n_channels: %d \n", n_channels);
	
	int count = 0;
	for(int c = 0; c < n_channels; c++){
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){
				
				int wa = width - w -1;
				int ha = height;
				
				po = pixelsO + h * rowstride + w * n_channels + c;
				pa = pixelsA + h * rowstride + wa * n_channels + c;
						
				*pa = *po;
			}
		}
	}	
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufAlterada);
	g_object_unref(bufOriginal);	
}

static void espelharV(GtkWidget *widget, gpointer app)
{
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	GdkPixbuf *bufAlterada = gdk_pixbuf_copy(bufOriginal);
	
	int width, height, rowstride, n_channels;
	guchar *pixelsO, *pixelsA, *pa, *po;

	width = gdk_pixbuf_get_width (bufOriginal);
	height = gdk_pixbuf_get_height (bufOriginal);
	rowstride = gdk_pixbuf_get_rowstride(bufOriginal);
	pixelsO = gdk_pixbuf_get_pixels(bufOriginal);
	pixelsA = gdk_pixbuf_get_pixels(bufAlterada);
	n_channels = gdk_pixbuf_get_n_channels(bufOriginal);
	
	g_print("width: %d \n", width);
	g_print("height: %d \n", height);
	g_print("rowstride: %d \n", rowstride);
	g_print("pixels: %p \n", pixelsA);
	g_print("n_channels: %d \n", n_channels);
	
	int count = 0;
	for(int c = 0; c < n_channels; c++){
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){
				
				int wa = width;
				int ha = height - h - 1;
				
				po = pixelsO + h * rowstride + w * n_channels + c;
				pa = pixelsA + ha * rowstride + w * n_channels + c;
						
				*pa = *po;
			}
		}
	}	
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufAlterada);
	g_object_unref(bufOriginal);
}


static void cinzaf(GtkWidget *widget, gpointer app)
{
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	GdkPixbuf *bufAlterada = gdk_pixbuf_copy(bufOriginal);
	
	int width, height, rowstride, n_channels;
	guchar *pixelsO, *pixelsA, *pa, *po;
	
	width = gdk_pixbuf_get_width (bufOriginal);
	height = gdk_pixbuf_get_height (bufOriginal);
	rowstride = gdk_pixbuf_get_rowstride(bufOriginal);
	pixelsO = gdk_pixbuf_get_pixels(bufOriginal);
	pixelsA = gdk_pixbuf_get_pixels(bufAlterada);
	n_channels = gdk_pixbuf_get_n_channels(bufOriginal);
	
	g_print("width: %d \n", width);
	g_print("height: %d \n", height);
	g_print("rowstride: %d \n", rowstride);
	g_print("pixels: %p \n", pixelsA);
	g_print("n_channels: %d \n", n_channels);
	
	int count = 0;
	for(int w = 0; w < width; w++){
		for(int h = 0; h < height; h++){

			//g_print("valor: %d",count);
			po = pixelsO + h * rowstride + w * n_channels;
			u_char r = po[0];
			u_char g = po[1];
			u_char b = po[2];
			
			guchar cinza = 0.299 * r + 0.587 * g + 0.114 * b;
			
			pa = pixelsA + h * rowstride + w * n_channels;
			pa[0] = cinza;
			pa[1] = cinza;
			pa[2] = cinza;
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufAlterada);
	g_object_unref(bufOriginal);	
}

static void quantf(GtkWidget *widget, gpointer app)
{
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	GdkPixbuf *bufAlterada = gdk_pixbuf_copy(bufOriginal);
	GtkWidget *arq = g_object_get_data(G_OBJECT(app), "Quant");
	const gchar *arqPath = gtk_entry_get_text(GTK_ENTRY(arq));
	int n = atoi(arqPath);
	
	int width, height, rowstride, n_channels;
	guchar *pixelsO, *pixelsA, *pa, *po;
	
	width = gdk_pixbuf_get_width (bufOriginal);
	height = gdk_pixbuf_get_height (bufOriginal);
	rowstride = gdk_pixbuf_get_rowstride(bufOriginal);
	pixelsO = gdk_pixbuf_get_pixels(bufOriginal);
	pixelsA = gdk_pixbuf_get_pixels(bufAlterada);
	n_channels = gdk_pixbuf_get_n_channels(bufOriginal);
		
	u_char t1 = 0;
	u_char t2 = 0;
	
	for(int w = 0; w < width; w++){
		for(int h = 0; h < height; h++){
			
			po = pixelsO + h * rowstride + w * n_channels;	
			guchar temp = po[0];
			
			if(temp > t2)
			{
				t2 = temp;
			}
			if(temp < t1)
			{
				t1 = temp;
			}
		}
	}
	
	int tam_int = (t2 - t1 + 1);
	if(n >= tam_int)
	{
		return;
	}
	
	int tb = tam_int / n;
	
	g_print("width: %d \n", width);
	g_print("height: %d \n", height);
	g_print("n: %d \n", n);
	g_print("t1: %d \n", t1);
	g_print("t2: %d \n", t2);
	g_print("tam_int: %d \n", tam_int);
	g_print("tb: %d \n", tb);
	g_print("channels: %d \n", n_channels);
		
	for(int w = 0; w < width; w++){
		for(int h = 0; h < height; h++){

			po = pixelsO + h * rowstride + w * n_channels;
			u_char r = po[0];
			//char g = po[1];
			//char b = po[2];
				
			u_char novoTom = 0;
			u_char t = r;
			int ativou = 0;
			for(int i = 0; i < n+1; i++)
			{
				if( (double)t >= (double)t1 - 0.5 + (double)i * (double)tb && 
				(double)t < (double)t1 + 0.5 + (double)(i+1) * (double)tb)
				{	
					ativou = 1;		
					novoTom = ((double)t1 - 0.5 + (double)i * (double)tb + (double)t1 + 0.5 + (double)(i+1) * (double)tb)/2;				
					break;
				}
				if(ativou == 0 && i == n -1)
				{
				g_print("t1: %d \n", t1);
				g_print("t2: %d \n", t2);
				g_print("n: %d \n", n);
				g_print("tam_int: %d \n", tam_int);
				g_print("t %d \n", t);
				g_print("1c %f \n", (double)t1 - 0.5 + (double)i * (double)tb);
				g_print("2c %f \n", (double)t1 + 0.5 + (double)(i+1) * (double)tb);
				g_print("tom %u \n", t);
				g_print("tom novo: %u \n\n", novoTom);
				}	
			}
			
			
								
			pa = pixelsA + h * rowstride + w * n_channels;
			pa[0] = novoTom;
			pa[1] = novoTom;
			pa[2] = novoTom;
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufAlterada);
	g_object_unref(bufOriginal);	
}

static void salvarf(GtkWidget *widget, gpointer app){
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	gdk_pixbuf_savev(bufOriginal, "alterado", "jpeg", NULL, NULL , NULL);
}

static void ajustarBrilhof(GtkWidget *widget, gpointer app){
	
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	GdkPixbuf *bufAlterada = gdk_pixbuf_copy(bufOriginal);
	GtkWidget *arq = g_object_get_data(G_OBJECT(app), "Brilho");
	const gchar *arqPath = gtk_entry_get_text(GTK_ENTRY(arq));
	int brigth = atoi(arqPath);
	
	g_print("Brilho: %d \n", brigth);
	
	if(brigth > 255 || brigth < -255)
	{
		g_object_unref(bufAlterada);
		return;
	}
	
	int width, height, rowstride, n_channels;
	guchar *pixelsO, *pixelsA, *pa, *po;
	
	width = gdk_pixbuf_get_width (bufOriginal);
	height = gdk_pixbuf_get_height (bufOriginal);
	rowstride = gdk_pixbuf_get_rowstride(bufOriginal);
	pixelsO = gdk_pixbuf_get_pixels(bufOriginal);
	pixelsA = gdk_pixbuf_get_pixels(bufAlterada);
	n_channels = gdk_pixbuf_get_n_channels(bufOriginal);
	
	int count = 0;
	if(n_channels == 3)
	{
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){

				//g_print("valor: %d",count);
				po = pixelsO + h * rowstride + w * n_channels;
				u_char r = po[0];
				u_char g = po[1];
				u_char b = po[2];
				int rt = r + brigth;
				int gt = g + brigth;
				int bt = b + brigth;
				
				
				pa = pixelsA + h * rowstride + w * n_channels;
				
				if(rt > 255) pa[0] = 255;
				else if (rt < 0) pa[0] = 0;
				else pa[0] = rt;
				
				if(gt > 255) pa[1] = 255;
				else if (gt < 0) pa[1] = 0;
				else pa[1] = gt;
				
				if(bt > 255) pa[2] = 255;
				else if (bt < 0) pa[2] = 0;
				else pa[2] = bt;
				
			}
		}
	}
	else //Caso 1 canal
	{
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){

				//g_print("valor: %d",count);
				po = pixelsO + h * rowstride + w * n_channels;
				u_char r = po[0];
				int rt = r + brigth;

				pa = pixelsA + h * rowstride + w * n_channels;
				
				if(rt > 255) pa[0] = 255;
				else if (rt < 0) pa[0] = 0;
				else pa[0] = rt;
			}
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufAlterada);
	g_object_unref(bufOriginal);	
}

int* imgParaHist(GdkPixbuf *bufImagem);

static void histogramaf(GtkWidget *widget, gpointer app)
{
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GtkWidget *imgHist = g_object_get_data(G_OBJECT(app), "Histograma");
	
	GdkPixbuf *bufImg = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	GdkPixbuf *bufHist= gtk_image_get_pixbuf(GTK_IMAGE(imgHist));
	
	int width, height, rowstride, n_channels;
	guchar *pixelsO, *pixelsA, *pa, *po;
	
	width = gdk_pixbuf_get_width (bufImg);
	height = gdk_pixbuf_get_height (bufImg);
	int totalPixels = width*height;
	int* histogramaArray =  imgParaHist(bufImg);
	
	FILE *p = popen("gnuplot", "w");
	fprintf(p, "set style data histograms\n");
	fprintf(p, "set style fill solid\n");
	fprintf(p, "set xrange [0:256]\n");
	fprintf(p, "unset xtics \n");
	fprintf(p, "set terminal jpeg size 700,300\n");
	fprintf(p, "set output 'hist.jpg'\n");
	fprintf(p, "plot '-' using 2:xtic(1) \n");	//using 2:xtic(1)
	
	g_print("total de pixels: %d", totalPixels);
	for(int i = 0; i < 256; i++)
	{
		fprintf(p, "%d %d\n", i, *(histogramaArray + i));
		g_print("%d - %d\n", i, *(histogramaArray + i));
	}
	fprintf(p, "e\n");
	pclose(p);
	
	gtk_image_set_from_file(GTK_IMAGE(imgHist), "hist.jpg");
	
}

static void ajustarContrastef(GtkWidget *widget, gpointer app){
	
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	GdkPixbuf *bufAlterada = gdk_pixbuf_copy(bufOriginal);
	GtkWidget *arq = g_object_get_data(G_OBJECT(app), "Contraste");
	const gchar *arqPath = gtk_entry_get_text(GTK_ENTRY(arq));
	int contrast = atoi(arqPath);
	
	g_print("Contraste: %d \n", contrast);
	
	if(contrast > 255 || contrast < 1)
	{
		g_object_unref(bufAlterada);
		return;
	}
	
	int width, height, rowstride, n_channels;
	guchar *pixelsO, *pixelsA, *pa, *po;
	
	width = gdk_pixbuf_get_width (bufOriginal);
	height = gdk_pixbuf_get_height (bufOriginal);
	rowstride = gdk_pixbuf_get_rowstride(bufOriginal);
	pixelsO = gdk_pixbuf_get_pixels(bufOriginal);
	pixelsA = gdk_pixbuf_get_pixels(bufAlterada);
	n_channels = gdk_pixbuf_get_n_channels(bufOriginal);
	
	int count = 0;
	if(n_channels == 3)
	{
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){

				//g_print("valor: %d",count);
				po = pixelsO + h * rowstride + w * n_channels;
				u_char r = po[0];
				u_char g = po[1];
				u_char b = po[2];
				int rt = r * contrast;
				int gt = g * contrast;
				int bt = b * contrast;
				
				
				pa = pixelsA + h * rowstride + w * n_channels;
				
				if(rt > 255) pa[0] = 255;
				else if (rt < 0) pa[0] = 0;
				else pa[0] = rt;
				
				if(gt > 255) pa[1] = 255;
				else if (gt < 0) pa[1] = 0;
				else pa[1] = gt;
				
				if(bt > 255) pa[2] = 255;
				else if (bt < 0) pa[2] = 0;
				else pa[2] = bt;
				
			}
		}
	}
	else //Caso 1 canal
	{
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){

				//g_print("valor: %d",count);
				po = pixelsO + h * rowstride + w * n_channels;
				u_char r = po[0];
				int rt = r * contrast;

				pa = pixelsA + h * rowstride + w * n_channels;
				
				if(rt > 255) pa[0] = 255;
				else if (rt < 0) pa[0] = 0;
				else pa[0] = rt;
			}
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufAlterada);
	g_object_unref(bufOriginal);	
}

static void negativof(GtkWidget *widget, gpointer app){
	
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	GdkPixbuf *bufAlterada = gdk_pixbuf_copy(bufOriginal);

	
	int width, height, rowstride, n_channels;
	guchar *pixelsO, *pixelsA, *pa, *po;
	
	width = gdk_pixbuf_get_width (bufOriginal);
	height = gdk_pixbuf_get_height (bufOriginal);
	rowstride = gdk_pixbuf_get_rowstride(bufOriginal);
	pixelsO = gdk_pixbuf_get_pixels(bufOriginal);
	pixelsA = gdk_pixbuf_get_pixels(bufAlterada);
	n_channels = gdk_pixbuf_get_n_channels(bufOriginal);
	
	if(n_channels == 3)
	{
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){

				//g_print("valor: %d",count);
				po = pixelsO + h * rowstride + w * n_channels;
				u_char r = po[0];
				u_char g = po[1];
				u_char b = po[2];
				u_char rt = 255 - r;
				u_char gt = 255 - g;
				u_char bt = 255 - b;
				
				pa = pixelsA + h * rowstride + w * n_channels;
				pa[0] = rt;
				pa[1] = gt;
				pa[2] = bt;
				
			}
		}
	}
	else //Caso 1 canal
	{
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){

				//g_print("valor: %d",count);
				po = pixelsO + h * rowstride + w * n_channels;
				u_char r = po[0];
				u_char rt = 255 - r;

				pa = pixelsA + h * rowstride + w * n_channels;
				
				pa[0] = rt;
			}
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufAlterada);
	g_object_unref(bufOriginal);	
}

//Guarda o Histograma
int* imgParaHist(GdkPixbuf *bufImagem)
{
	//conversão da img par apixbuf
	//GdkPixbuf *bufImagem = gtk_image_get_pixbuf(GTK_IMAGE(widget));
	
	static int histogramaArray[256];
	
	for(int i = 0; i < 256; i++)
	{
		histogramaArray[i] = 0;
	}
	
	//Pega o numero de canais
	int channels = gdk_pixbuf_get_n_channels(bufImagem);
	int width = gdk_pixbuf_get_width (bufImagem);
	int height = gdk_pixbuf_get_height (bufImagem);
	int rowstride = gdk_pixbuf_get_rowstride(bufImagem);
	
	//int totalDePixels = width*height;
	guchar *pixels = gdk_pixbuf_get_pixels(bufImagem); //inicio dos pixels
	
	if(channels == 1)
	{
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){
				
				guchar *pixel = pixels + h * rowstride + w * channels;
				u_char lum = pixel[0];
				histogramaArray[lum]++;
			
			}
		}
		
	}
	else if(channels = 3)
	{
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){
				
				guchar *pixel = pixels + h * rowstride + w * channels;
				u_char r = pixel[0];
				u_char g = pixel[1];
				u_char b = pixel[2];
				
				guchar lum = 0.299 * r + 0.587 * g + 0.114 * b;
				histogramaArray[lum]++;
			}
		}			
	}
	else
	{
		g_print("Problema no calcularHist, n de canais diferente de 1 ou 3");
	}
	return histogramaArray;
}

static void equalizarf(GtkWidget *widget, gpointer app){
	
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	GdkPixbuf *bufAlterada = gdk_pixbuf_copy(bufOriginal);

	
	int width, height, rowstride, n_channels;
	guchar *pixelsO, *pixelsA, *pa, *po;
	
	width = gdk_pixbuf_get_width (bufOriginal);
	height = gdk_pixbuf_get_height (bufOriginal);
	rowstride = gdk_pixbuf_get_rowstride(bufOriginal);
	pixelsO = gdk_pixbuf_get_pixels(bufOriginal);
	pixelsA = gdk_pixbuf_get_pixels(bufAlterada);
	n_channels = gdk_pixbuf_get_n_channels(bufOriginal);
	
	int totalPixels = width * height;
	int* histograma = imgParaHist(bufOriginal);
	float alpha = 255.0/ totalPixels;
	int* histogramaCumulativo = malloc(sizeof(int)*256);
	
	
	//histograma cumulativo
	g_print("Alpha: %f \n", alpha);
	histogramaCumulativo[0] = alpha * *(histograma);
	for(int i = 1; i < 256; i++)
	{
		histogramaCumulativo[i] =  histogramaCumulativo[i-1] + round(alpha * (float)*(histograma + i));
		g_print("Equa: valor %d - hist %d - histc %d \n", i, *(histograma + i),  histogramaCumulativo[i]);
	}
	
	if(n_channels == 3)
	{
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){

				//g_print("valor: %d",count);
				po = pixelsO + h * rowstride + w * n_channels;
				u_char r = po[0];
				u_char g = po[1];
				u_char b = po[2];
				u_char rt = histogramaCumulativo[r];
				u_char gt = histogramaCumulativo[g];
				u_char bt = histogramaCumulativo[b];
				
				pa = pixelsA + h * rowstride + w * n_channels;
				pa[0] = rt;
				pa[1] = gt;
				pa[2] = bt;
				
			}
		}
	}
	else //Caso 1 canal
	{
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){

				//g_print("valor: %d",count);
				po = pixelsO + h * rowstride + w * n_channels;
				u_char r = po[0];
				u_char rt = histogramaCumulativo[r]; // novo valor de cinza
				
				pa = pixelsA + h * rowstride + w * n_channels;	
				pa[0] = rt;
			}
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufAlterada);
	g_object_unref(bufOriginal);	
	free(histogramaCumulativo);
}

static void matchingf(GtkWidget *widget, gpointer app){
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufSrc = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	GdkPixbuf *bufResultado= gdk_pixbuf_copy(bufSrc);
	
	GtkWidget *arq = g_object_get_data(G_OBJECT(app), "MathingIMG");
	const gchar *arqPath = gtk_entry_get_text(GTK_ENTRY(arq));
	
	GdkPixbuf *bufTarget = gdk_pixbuf_new_from_file(arqPath, NULL);
	
	//Histograma das duas imagens
	int* histoTemp = imgParaHist(bufSrc);
	int* histogramaSrc = malloc(sizeof(int)*256);
	memcpy(histogramaSrc, histoTemp, sizeof(int)*256);
	
	histoTemp = imgParaHist(bufTarget);
	int* histogramaTarget = malloc(sizeof(int)*256);
	memcpy(histogramaTarget, histoTemp, sizeof(int)*256);
	
	
	//HistogramaCumulativo
	int* histogramaCumulativoSrc = malloc(sizeof(int)*256);
	int* histogramaCumulativoTarget= malloc(sizeof(int)*256);
	
	int widthSrc = gdk_pixbuf_get_width (bufSrc);
	int heightSrc = gdk_pixbuf_get_height (bufSrc);
	int widthTarget = gdk_pixbuf_get_width (bufTarget);
	int heightTarget  = gdk_pixbuf_get_height (bufTarget);
	
	
	//Src Primeiro
	int totalPixelsSrc = widthSrc * heightSrc;
	float alphaSrc = 255.0/ totalPixelsSrc;
	g_print("Alpha SRC: %f \n", alphaSrc);
	histogramaCumulativoSrc[0] = alphaSrc * *(histogramaSrc);
	for(int i = 1; i < 256; i++)
	{
		histogramaCumulativoSrc[i] =  histogramaCumulativoSrc[i-1] + round(alphaSrc * (float)*(histogramaSrc + i));
		g_print("Equa: valor %d - hist %d - histc %d \n", i, *(histogramaSrc + i),  histogramaCumulativoSrc[i]);
	}
	
	//Target Segundo
	int totalPixelsTarget= widthTarget * heightTarget;
	float alphaTarget = 255.0/ totalPixelsTarget;
	g_print("Alpha Target: %f \n", alphaTarget);
	histogramaCumulativoTarget[0] = alphaTarget * *(histogramaTarget);
	for(int i = 1; i < 256; i++)
	{
		histogramaCumulativoTarget[i] =  histogramaCumulativoTarget[i-1] + round(alphaTarget * (float)*(histogramaTarget + i));
		g_print("Equa: valor %d - hist %d - histc %d \n", i, *(histogramaTarget + i),  histogramaCumulativoTarget[i]);
	}
	
	int* HM = malloc(sizeof(int)*256);
	
	for(int i = 0; i < 256; i++)
	{
		int valorSrc = histogramaCumulativoSrc[i];
		int valor = 2147483647;
		int lum = 0;
		for(int z = 0; z < 256; z++)
		{
			int valorTarget = histogramaCumulativoTarget[z];
			if(valor > abs(valorSrc - valorTarget))
			{
				valor = abs(valorSrc - valorTarget);	
				lum = z;
				//g_print("HM: pos %d  -  valorSrc %d - valorTarget %d - lum %d - abd %d \n", z, valorSrc, valorTarget, lum, valor);
			}
			//g_print("HM: pos %d  -  valorSrc %d - valorTarget %d - lum %d - abd %d \n", z, valorSrc, valorTarget, lum, valor);
		}
		
		*(HM + i) = lum;
		g_print("HM: pos %d - valor %d \n", i, *(HM + i));	
	}
	
	//Passa para a imagem
	int width, height, rowstride, n_channels;
	guchar *pixelsO, *pixelsA, *pa, *po;
	
	width = gdk_pixbuf_get_width (bufSrc);
	height = gdk_pixbuf_get_height (bufSrc);
	rowstride = gdk_pixbuf_get_rowstride(bufSrc);
	pixelsO = gdk_pixbuf_get_pixels(bufSrc);
	pixelsA = gdk_pixbuf_get_pixels(bufResultado);
	n_channels = gdk_pixbuf_get_n_channels(bufSrc);
	
	
	if(n_channels == 3)
	{
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){

				//g_print("valor: %d",count);
				po = pixelsO + h * rowstride + w * n_channels;
				u_char r = po[0];
				u_char g = po[1];
				u_char b = po[2];
				u_char rt = HM[r];
				u_char gt = HM[g];
				u_char bt = HM[b];
				
				pa = pixelsA + h * rowstride + w * n_channels;
				pa[0] = rt;
				pa[1] = gt;
				pa[2] = bt;
				
			}
		}
	}
	else //Caso 1 canal
	{
		for(int w = 0; w < width; w++){
			for(int h = 0; h < height; h++){

				//g_print("valor: %d",count);
				po = pixelsO + h * rowstride + w * n_channels;
				u_char r = po[0];
				u_char rt = HM[r]; // novo valor de cinza
				
				pa = pixelsA + h * rowstride + w * n_channels;	
				pa[0] = rt;
			}
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufResultado);
	g_object_unref(bufSrc);
	g_object_unref(bufTarget);	
	
	free(histogramaSrc);
	free(histogramaTarget);
	free(histogramaCumulativoSrc);
	free(histogramaCumulativoTarget);
	free(HM);
}

u_char getPixelR(int x, int y, GdkPixbuf *buf){
	int nChannels = gdk_pixbuf_get_n_channels(buf);
	int rowstride = gdk_pixbuf_get_rowstride(buf);
	
	if(x < 0 || y < 0)
	{
		g_print("Erro na consulta do pixel x: %d y: %d\n", x, y);
		return 0;
	}
	
	guchar *inicio = gdk_pixbuf_get_pixels(buf);
	guchar *pixel = inicio + y * rowstride + x * nChannels;
	guchar resposta = pixel[0];
	return resposta;
}
u_char getPixelG(int x, int y, GdkPixbuf *buf){
	int nChannels = gdk_pixbuf_get_n_channels(buf);
	int rowstride = gdk_pixbuf_get_rowstride(buf);
	
	if(x < 0 || y < 0)
	{
		g_print("Erro na consulta do pixel x: %d y: %d\n", x, y);
		return 0;
	}
	
	guchar *inicio = gdk_pixbuf_get_pixels(buf);
	guchar *pixel = inicio + y * rowstride + x * nChannels;
	guchar resposta = pixel[1];
	return resposta;
}
u_char getPixelB(int x, int y, GdkPixbuf *buf){
	int nChannels = gdk_pixbuf_get_n_channels(buf);
	int rowstride = gdk_pixbuf_get_rowstride(buf);
	
	if(x < 0 || y < 0)
	{
		g_print("Erro na consulta do pixel x: %d y: %d\n", x, y);
		return 0;
	}
	
	guchar *inicio = gdk_pixbuf_get_pixels(buf);
	guchar *pixel = inicio + y * rowstride + x * nChannels;
	guchar resposta = pixel[2];
	return resposta;
}

static void setPixelR(int x, int y, u_char valor, GdkPixbuf *buf){
	int nChannels = gdk_pixbuf_get_n_channels(buf);
	int rowstride = gdk_pixbuf_get_rowstride(buf);
	
	if(x < 0 || y < 0)
	{
		g_print("Erro na inserção do pixel x: %d y: %d valor: %d\n", x, y, valor);
		return;
	}
	
	guchar *inicio = gdk_pixbuf_get_pixels(buf);
	guchar *pixel = inicio + y * rowstride + x * nChannels;
	pixel[0] = valor;
}
static void setPixelG(int x, int y, u_char valor, GdkPixbuf *buf){
	int nChannels = gdk_pixbuf_get_n_channels(buf);
	int rowstride = gdk_pixbuf_get_rowstride(buf);
	
	if(x < 0 || y < 0)
	{
		g_print("Erro na inserção do pixel x: %d y: %d valor: %d\n", x, y, valor);
		return;
	}
	
	guchar *inicio = gdk_pixbuf_get_pixels(buf);
	guchar *pixel = inicio + y * rowstride + x * nChannels;
	pixel[1] = valor;
}
static void setPixelB(int x, int y, u_char valor, GdkPixbuf *buf){
	int nChannels = gdk_pixbuf_get_n_channels(buf);
	int rowstride = gdk_pixbuf_get_rowstride(buf);
	
	if(x < 0 || y < 0)
	{
		g_print("Erro na inserção do pixel x: %d y: %d valor: %d\n", x, y, valor);
		return;
	}
	
	guchar *inicio = gdk_pixbuf_get_pixels(buf);
	guchar *pixel = inicio + y * rowstride + x * nChannels;
	pixel[2] = valor;
}


static void zoomOutf(GtkWidget *widget, gpointer app){
	//Fatores S
	GtkWidget *wSX = g_object_get_data(G_OBJECT(app), "SX");
	GtkWidget *wSY = g_object_get_data(G_OBJECT(app), "SY");
	const gchar *cSX  = gtk_entry_get_text(GTK_ENTRY(wSX));
	const gchar *cSY = gtk_entry_get_text(GTK_ENTRY(wSY));
	int SX = atoi(cSX);
	int SY = atoi(cSY);
	
	if(SX < 1 || SY < 1)
	{
		g_print("SX ou SY invalido, valor tem q ser positivo\n");
		return;
	}
		
	//Imagem Original
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	int widthOriginal= gdk_pixbuf_get_width (bufOriginal);
	int heightOriginal = gdk_pixbuf_get_height (bufOriginal);
	int nChannels = gdk_pixbuf_get_n_channels(bufOriginal);
	int rowstride = gdk_pixbuf_get_rowstride(bufOriginal);
	guchar *pixelsO = gdk_pixbuf_get_pixels(bufOriginal);
	
	
	//Imagem Nova
	int widthNova= widthOriginal / SX;
	int heightNova = heightOriginal / SY;
		
	GdkPixbuf *bufResultado = gdk_pixbuf_new (GDK_COLORSPACE_RGB, FALSE, 8, widthNova, heightNova);
	int rowstrideR = gdk_pixbuf_get_rowstride(bufResultado);
	guchar *pixelsR = gdk_pixbuf_get_pixels(bufResultado);
	
	for(int h = 0; h < heightOriginal; h = h + SY){
		for(int w = 0; w < widthOriginal; w = w + SX){ //Itera quadrados
			int Xdestino = w / SX;
			int Ydestino = h / SY;
			int valorR = 0;
			int valorG = 0;
			int valorB = 0;
			int countPixelsValidos = 0;
			
			//itera dentro do quadrado
			for(int qh = 0; qh < SY; qh++){
				for(int qw = 0; qw < SX; qw++){
					int posicaoImgY = h + qh;
					int posicaoImgX = w + qw;
					if(posicaoImgY >= heightOriginal || posicaoImgX >= widthOriginal) continue;	//Não trata pixels fora da area da imagem
					
					valorR = valorR + getPixelR(posicaoImgX, posicaoImgY, bufOriginal);
					valorG = valorG + getPixelG(posicaoImgX, posicaoImgY, bufOriginal);
					valorB = valorB + getPixelB(posicaoImgX, posicaoImgY, bufOriginal);	
					countPixelsValidos++;
				}
			}
			//Set dos valores na imagem nova
			valorR = valorR / countPixelsValidos;
			valorG = valorG / countPixelsValidos;
			valorB = valorB / countPixelsValidos;
			
			setPixelR(Xdestino, Ydestino, valorR, bufResultado);
			setPixelG(Xdestino, Ydestino, valorG, bufResultado);
			setPixelB(Xdestino, Ydestino, valorB, bufResultado);
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufResultado);
	g_object_unref(bufOriginal);
}
static void zoomInf(GtkWidget *widget, gpointer app){
	//Fatores S
	int SX = 2;
	int SY = 2;
		
	//Imagem Original
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	int widthOriginal= gdk_pixbuf_get_width (bufOriginal);
	int heightOriginal = gdk_pixbuf_get_height (bufOriginal);
	int nChannels = gdk_pixbuf_get_n_channels(bufOriginal);
	int rowstride = gdk_pixbuf_get_rowstride(bufOriginal);
	guchar *pixelsO = gdk_pixbuf_get_pixels(bufOriginal);
	
	
	//Imagem Nova
	int widthNova= widthOriginal * SX;
	int heightNova = heightOriginal * SY;
		
	GdkPixbuf *bufResultado = gdk_pixbuf_new (GDK_COLORSPACE_RGB, FALSE, 8, widthNova, heightNova);
	int rowstrideR = gdk_pixbuf_get_rowstride(bufResultado);
	guchar *pixelsR = gdk_pixbuf_get_pixels(bufResultado);
	
	//copia os pixels originais
	for(int h = 0; h < heightOriginal; h++){
		for(int w = 0; w < widthOriginal; w++){
			u_char r = getPixelR(w, h, bufOriginal);
			u_char g = getPixelG(w, h, bufOriginal);
			u_char b = getPixelB(w, h, bufOriginal);
			
			setPixelR(w*2, h*2, r, bufResultado);
			setPixelG(w*2, h*2, g, bufResultado);
			setPixelB(w*2, h*2, b, bufResultado);
			
			if(w != 0 && h!= 0){//prenche vão das colunas
				
				u_char ra = getPixelR(w-1, h, bufOriginal);
				u_char ga = getPixelG(w-1, h, bufOriginal);
				u_char ba = getPixelB(w-1, h, bufOriginal);
				
				int rColuna = (r + ra) / 2;
				int gColuna = (g + ga) / 2;
				int bColuna = (b + ba) / 2;
				
				//g_print("inserção x: %d y: %d - valor: %d", w*2-1, h*2-1, rColuna);
				
				setPixelR(w*2-1, h*2, rColuna, bufResultado);
				setPixelG(w*2-1, h*2, gColuna, bufResultado);
				setPixelB(w*2-1, h*2, bColuna, bufResultado);	
			}	
			if(w != 0 && h!= 0){//prenche vão das linhas
				
				u_char ra = getPixelR(w, h-1, bufOriginal);
				u_char ga = getPixelG(w, h-1, bufOriginal);
				u_char ba = getPixelB(w, h-1, bufOriginal);
				
				int rLinha = (r + ra) / 2;
				int gLinha = (g + ga) / 2;
				int bLinha = (b + ba) / 2;
				
				//g_print("inserção x: %d y: %d - valor: %d", w*2-1, h*2-1, rColuna);
				
				setPixelR(w*2, h*2-1, rLinha, bufResultado);
				setPixelG(w*2, h*2-1, gLinha, bufResultado);
				setPixelB(w*2, h*2-1, bLinha, bufResultado);	
			}
			if(w != 0 && h!= 0){//prenche vão do meio
				
				u_char r1 = getPixelR(w, h-1, bufOriginal);
				u_char g1 = getPixelG(w, h-1, bufOriginal);
				u_char b1 = getPixelB(w, h-1, bufOriginal);
				
				u_char r2 = getPixelR(w-1, h, bufOriginal);
				u_char g2 = getPixelG(w-1, h, bufOriginal);
				u_char b2 = getPixelB(w-1, h, bufOriginal);
				
				u_char r3 = getPixelR(w-1, h-1, bufOriginal);
				u_char g3 = getPixelG(w-1, h-1, bufOriginal);
				u_char b3 = getPixelB(w-1, h-1, bufOriginal);
				
				int rMeio = (r + r1 + r2 + r3) / 4;
				int gMeio = (g + g1 + g2 + g3) / 4;
				int bMeio = (b + b1 + b2 + b3) / 4;
				
				//g_print("inserção x: %d y: %d - valor: %d", w*2-1, h*2-1, rColuna);
				
				setPixelR(w*2-1, h*2-1, rMeio, bufResultado);
				setPixelG(w*2-1, h*2-1, gMeio, bufResultado);
				setPixelB(w*2-1, h*2-1, bMeio, bufResultado);	
			}
			
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufResultado);
	g_object_unref(bufOriginal);
}
static void ghf(GtkWidget *widget, gpointer app){
	//Imagem Original
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	int widthOriginal= gdk_pixbuf_get_width (bufOriginal);
	int heightOriginal = gdk_pixbuf_get_height (bufOriginal);
	int nChannels = gdk_pixbuf_get_n_channels(bufOriginal);
	int rowstride = gdk_pixbuf_get_rowstride(bufOriginal);
	guchar *pixelsO = gdk_pixbuf_get_pixels(bufOriginal);
	
	//Imagem Nova
	int widthNova= heightOriginal;
	int heightNova = widthOriginal;
		
	GdkPixbuf *bufResultado = gdk_pixbuf_new (GDK_COLORSPACE_RGB, FALSE, 8, widthNova, heightNova);
	int rowstrideR = gdk_pixbuf_get_rowstride(bufResultado);
	guchar *pixelsR = gdk_pixbuf_get_pixels(bufResultado);
	
	for(int h = 0; h < heightOriginal; h++){
		for(int w = 0; w < widthOriginal; w++){
			u_char r = getPixelR(w, h, bufOriginal);
			u_char g = getPixelG(w, h, bufOriginal);
			u_char b = getPixelB(w, h, bufOriginal);
			

			setPixelR(widthNova -h -1, w, r, bufResultado);
			setPixelG(widthNova -h -1, w, g, bufResultado);
			setPixelB(widthNova -h -1, w, b, bufResultado);
		
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufResultado);
	g_object_unref(bufOriginal);
}
static void gahf(GtkWidget *widget, gpointer app){
	//Imagem Original
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	int widthOriginal= gdk_pixbuf_get_width (bufOriginal);
	int heightOriginal = gdk_pixbuf_get_height (bufOriginal);
	int nChannels = gdk_pixbuf_get_n_channels(bufOriginal);
	int rowstride = gdk_pixbuf_get_rowstride(bufOriginal);
	guchar *pixelsO = gdk_pixbuf_get_pixels(bufOriginal);
	
	//Imagem Nova
	int widthNova= heightOriginal;
	int heightNova = widthOriginal;
		
	GdkPixbuf *bufResultado = gdk_pixbuf_new (GDK_COLORSPACE_RGB, FALSE, 8, widthNova, heightNova);
	int rowstrideR = gdk_pixbuf_get_rowstride(bufResultado);
	guchar *pixelsR = gdk_pixbuf_get_pixels(bufResultado);
	
	for(int h = 0; h < heightOriginal; h++){
		for(int w = 0; w < widthOriginal; w++){
			u_char r = getPixelR(w, h, bufOriginal);
			u_char g = getPixelG(w, h, bufOriginal);
			u_char b = getPixelB(w, h, bufOriginal);
			

			
			setPixelR(h, heightNova -w -1, r, bufResultado);
			setPixelG(h, heightNova -w -1, g, bufResultado);
			setPixelB(h, heightNova -w -1, b, bufResultado);
		
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufResultado);
	g_object_unref(bufOriginal);
}


static void aplicarFiltro(double *kernel, GdkPixbuf *buf,  GdkPixbuf *novoBuf, int x, int y){
	//COloca o filtro em uma matriz 3x3
	double kmatrix[3][3];
	//g_print("Matrix \n");
	for(int c = 0; c < 3; c++){
		for(int l = 0; l < 3; l++){
			kmatrix[l][c] = *(kernel + c + 3*l);
			//g_print("[%f] ", *(kernel + c + 3*l));
		}
		//g_print("\n");
	}	
	
	//inverte a matriz
	double kmatrixinvertida[3][3];
	//g_print("Matrix Invertida\n");
	for(int c = 0; c < 3; c++){
		for(int l = 0; l < 3; l++){
			kmatrixinvertida[l][c] = kmatrix[2-l][2-c];	
			//g_print("[%f] ", kmatrixinvertida[l][c]);
		}
		//g_print("\n");
	}
	
	int width = gdk_pixbuf_get_width (buf);
	int height= gdk_pixbuf_get_height (buf);
	

	
	int resultador = 0;
	int resultadog = 0;
	int resultadob = 0;
	//Aplica o filtro
	for(int c = -1; c < 2; c++){
		for(int l = -1; l < 2; l++){
			if(x + c < 0 || y + l < 0) continue; //Ignora itens fora da area
			if(x + c >= width || y + l >= height) continue; //Ignora itens fora da area

			u_char r = getPixelR(x + c, y + l, buf);
			u_char g = getPixelG(x + c, y + l, buf);
			u_char b = getPixelB(x + c, y + l, buf);	
			
			resultador = resultador + kmatrixinvertida[c + 1][l + 1]*r;
			resultadog = resultadog + kmatrixinvertida[c + 1][l + 1]*g;
			resultadob = resultadob + kmatrixinvertida[c + 1][l + 1]*b;
		}
	}
	
	if(resultador > 255) resultador = 255;
	if(resultadog > 255) resultadog = 255;
	if(resultadob > 255) resultadob = 255;
	if(resultador < 0) resultador = 0;
	if(resultadog < 0) resultadog = 0;
	if(resultadob < 0) resultadob = 0;
	
	//g_print("Filtro X: %d Y: %d VALOR: %d\n", x , y, resultador);
	
	setPixelR(x, y, (u_char)resultador, novoBuf);
	setPixelG(x, y, (u_char)resultadog, novoBuf);
	setPixelB(x, y, (u_char)resultadob, novoBuf);
}

static void gaussf(GtkWidget *widget, gpointer app){
	g_print("Gaussiano\n");
	//Imagem Original
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	int widthOriginal= gdk_pixbuf_get_width (bufOriginal);
	int heightOriginal = gdk_pixbuf_get_height (bufOriginal);
	
	g_print("width %d - heigth %d\n", widthOriginal, heightOriginal);
	
	//Imagem Nova
		
	GdkPixbuf *bufResultado = gdk_pixbuf_copy(bufOriginal);
	int rowstrideR = gdk_pixbuf_get_rowstride(bufResultado);
	guchar *pixelsR = gdk_pixbuf_get_pixels(bufResultado);
	
	//filtro
	
	double kernel[] = {0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625};
	
	for(int h = 0; h < heightOriginal; h++){
		for(int w = 0; w < widthOriginal; w++){
			aplicarFiltro(kernel, bufOriginal, bufResultado, w, h);			
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufResultado);
	g_object_unref(bufOriginal);	
}
static void laplaf(GtkWidget *widget, gpointer app){
	g_print("laplaciano\n");
	//Imagem Original
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	int widthOriginal= gdk_pixbuf_get_width (bufOriginal);
	int heightOriginal = gdk_pixbuf_get_height (bufOriginal);
	
	g_print("width %d - heigth %d\n", widthOriginal, heightOriginal);
	
	//Imagem Nova
		
	GdkPixbuf *bufResultado = gdk_pixbuf_copy(bufOriginal);
	int rowstrideR = gdk_pixbuf_get_rowstride(bufResultado);
	guchar *pixelsR = gdk_pixbuf_get_pixels(bufResultado);
	
	//filtro
	
	double kernel[] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
	
	for(int h = 0; h < heightOriginal; h++){
		for(int w = 0; w < widthOriginal; w++){
			aplicarFiltro(kernel, bufOriginal, bufResultado, w, h);			
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufResultado);
	g_object_unref(bufOriginal);

}
static void passaAf(GtkWidget *widget, gpointer app){
	
	g_print("Passa Altas Generico\n");
	//Imagem Original
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	int widthOriginal= gdk_pixbuf_get_width (bufOriginal);
	int heightOriginal = gdk_pixbuf_get_height (bufOriginal);
	
	g_print("width %d - heigth %d\n", widthOriginal, heightOriginal);
	
	//Imagem Nova
		
	GdkPixbuf *bufResultado = gdk_pixbuf_copy(bufOriginal);
	int rowstrideR = gdk_pixbuf_get_rowstride(bufResultado);
	guchar *pixelsR = gdk_pixbuf_get_pixels(bufResultado);
	
	//filtro
	
	double kernel[] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
	
	for(int h = 0; h < heightOriginal; h++){
		for(int w = 0; w < widthOriginal; w++){
			aplicarFiltro(kernel, bufOriginal, bufResultado, w, h);			
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufResultado);
	g_object_unref(bufOriginal);
	
}
static void PrewittHxf(GtkWidget *widget, gpointer app){
	g_print("Prewitt Hx \n");
	//Imagem Original
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	int widthOriginal= gdk_pixbuf_get_width (bufOriginal);
	int heightOriginal = gdk_pixbuf_get_height (bufOriginal);
	
	g_print("width %d - heigth %d\n", widthOriginal, heightOriginal);
	
	//Imagem Nova
		
	GdkPixbuf *bufResultado = gdk_pixbuf_copy(bufOriginal);
	int rowstrideR = gdk_pixbuf_get_rowstride(bufResultado);
	guchar *pixelsR = gdk_pixbuf_get_pixels(bufResultado);
	
	//filtro
	
	double kernel[] = {-1, -0, 1, -1, 0, 1, -1, 0, 1};
	
	for(int h = 0; h < heightOriginal; h++){
		for(int w = 0; w < widthOriginal; w++){
			aplicarFiltro(kernel, bufOriginal, bufResultado, w, h);			
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufResultado);
	g_object_unref(bufOriginal);
}
static void PrewittHyf(GtkWidget *widget, gpointer app){
	g_print("Prewitt Hy\n");
	//Imagem Original
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	int widthOriginal= gdk_pixbuf_get_width (bufOriginal);
	int heightOriginal = gdk_pixbuf_get_height (bufOriginal);
	
	g_print("width %d - heigth %d\n", widthOriginal, heightOriginal);
	
	//Imagem Nova
		
	GdkPixbuf *bufResultado = gdk_pixbuf_copy(bufOriginal);
	int rowstrideR = gdk_pixbuf_get_rowstride(bufResultado);
	guchar *pixelsR = gdk_pixbuf_get_pixels(bufResultado);
	
	//filtro
	
	double kernel[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	
	for(int h = 0; h < heightOriginal; h++){
		for(int w = 0; w < widthOriginal; w++){
			aplicarFiltro(kernel, bufOriginal, bufResultado, w, h);			
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufResultado);
	g_object_unref(bufOriginal);
}
static void sobelHxf(GtkWidget *widget, gpointer app){
	g_print("Sobel Hx\n");
	//Imagem Original
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	int widthOriginal= gdk_pixbuf_get_width (bufOriginal);
	int heightOriginal = gdk_pixbuf_get_height (bufOriginal);
	
	g_print("width %d - heigth %d\n", widthOriginal, heightOriginal);
	
	//Imagem Nova
		
	GdkPixbuf *bufResultado = gdk_pixbuf_copy(bufOriginal);
	int rowstrideR = gdk_pixbuf_get_rowstride(bufResultado);
	guchar *pixelsR = gdk_pixbuf_get_pixels(bufResultado);
	
	//filtro
	
	double kernel[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
	
	for(int h = 0; h < heightOriginal; h++){
		for(int w = 0; w < widthOriginal; w++){
			aplicarFiltro(kernel, bufOriginal, bufResultado, w, h);			
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufResultado);
	g_object_unref(bufOriginal);
}
static void sobelHyf(GtkWidget *widget, gpointer app){
	g_print("Sobel Hx\n");
	//Imagem Original
	GtkWidget *imgAlterada = g_object_get_data(G_OBJECT(app), "Alterada");
	GdkPixbuf *bufOriginal = gtk_image_get_pixbuf(GTK_IMAGE(imgAlterada));
	
	int widthOriginal= gdk_pixbuf_get_width (bufOriginal);
	int heightOriginal = gdk_pixbuf_get_height (bufOriginal);
	
	g_print("width %d - heigth %d\n", widthOriginal, heightOriginal);
	
	//Imagem Nova
		
	GdkPixbuf *bufResultado = gdk_pixbuf_copy(bufOriginal);
	int rowstrideR = gdk_pixbuf_get_rowstride(bufResultado);
	guchar *pixelsR = gdk_pixbuf_get_pixels(bufResultado);
	
	//filtro
	
	double kernel[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
	
	for(int h = 0; h < heightOriginal; h++){
		for(int w = 0; w < widthOriginal; w++){
			aplicarFiltro(kernel, bufOriginal, bufResultado, w, h);			
		}
	}
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(imgAlterada), bufResultado);
	g_object_unref(bufOriginal);
}



static void activate(GtkApplication *app, gpointer user_data){
	GtkWidget *window;
	GtkWidget *janelaOriginal;
	GtkWidget *janelaAlterada;	
	GtkWidget *histograma;
	GtkWidget *histogramaAlterado;
	GtkWidget *button_box;
	
	//Janela Botoes
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Comandos");
	gtk_window_set_default_size(GTK_WINDOW(window),  200, 200);
	button_box = gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
	gtk_container_add (GTK_CONTAINER (window), button_box);
	
	
	
	//Janelas Imagens
	janelaOriginal = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(janelaOriginal), "Img Original");
	gtk_window_set_default_size(GTK_WINDOW(janelaOriginal),  200, 200);
	janelaAlterada = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(janelaAlterada), "Img Alterada");
	gtk_window_set_default_size(GTK_WINDOW(janelaAlterada),  200, 200);
	histograma = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(histograma), "Histograma");
	gtk_window_set_default_size(GTK_WINDOW(histograma),  700, 300);
	histogramaAlterado = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(histogramaAlterado), "Histograma Alerado");
	gtk_window_set_default_size(GTK_WINDOW(histogramaAlterado),  700, 300);
		
	
	GtkWidget *imgOriginal = gtk_image_new_from_file("");
	gtk_container_add (GTK_CONTAINER (janelaOriginal), imgOriginal);
	GtkWidget *imgAlterada = gtk_image_new_from_file("");
	gtk_container_add (GTK_CONTAINER (janelaAlterada), imgAlterada);
	GtkWidget *imgHistograma = gtk_image_new_from_file("");
	gtk_container_add (GTK_CONTAINER (histograma), imgHistograma);
	GtkWidget *imgHistogramaAlterado = gtk_image_new_from_file("");
	gtk_container_add (GTK_CONTAINER (histogramaAlterado), imgHistogramaAlterado);

	

	//Botoes
	GtkWidget *arqNome = gtk_entry_new();
	GtkWidget *carregar = gtk_button_new_with_label("Carregar");
	GtkWidget *original = gtk_button_new_with_label("Original");
	GtkWidget *espVertical = gtk_button_new_with_label("Espelhar Vertical");
	GtkWidget *espHorizontal = gtk_button_new_with_label("Espelhar Horizontal");
	GtkWidget *cinza = gtk_button_new_with_label("Cinza");
	GtkWidget *quantEntry = gtk_entry_new();
	GtkWidget *quant = gtk_button_new_with_label("Quantização");
	GtkWidget *salvar = gtk_button_new_with_label("Salvar");
	GtkWidget *hist = gtk_button_new_with_label("Histograma");
	GtkWidget *ajustarBEntry = gtk_entry_new();
	GtkWidget *ajustarB = gtk_button_new_with_label("Ajustar Brilho");
	GtkWidget *ajustarCEntry = gtk_entry_new();
	GtkWidget *ajustarC = gtk_button_new_with_label("Ajustar Contraste");
	GtkWidget *negativo = gtk_button_new_with_label("Negativo");
	GtkWidget *equalizar = gtk_button_new_with_label("Equalizar");
	GtkWidget *matchingEntry = gtk_entry_new();
	GtkWidget *matching = gtk_button_new_with_label("Mathing");
	GtkWidget *sX = gtk_entry_new();
	GtkWidget *sY = gtk_entry_new();
	GtkWidget *zO = gtk_button_new_with_label("Zoom out");
	GtkWidget *zI = gtk_button_new_with_label("Zoom in");
	GtkWidget *gH = gtk_button_new_with_label("Girar Horario");
	GtkWidget *gAH = gtk_button_new_with_label("Girar AHorario");
	GtkWidget *gauss = gtk_button_new_with_label("Gausiano");
	GtkWidget *lapla = gtk_button_new_with_label("Laplaciano");
	GtkWidget *passaA = gtk_button_new_with_label("Passa Altas Genérico");
	GtkWidget *PrewittHx = gtk_button_new_with_label("Prewitt Hx");
	GtkWidget *PrewittHy = gtk_button_new_with_label("Prewitt Hy");
	GtkWidget *sobelHx = gtk_button_new_with_label("Sobel Hx");
	GtkWidget *sobelHy = gtk_button_new_with_label("Sobel Hy ");
	

	gtk_container_add(GTK_CONTAINER(button_box), arqNome);
	gtk_container_add(GTK_CONTAINER(button_box), carregar);
	gtk_container_add(GTK_CONTAINER(button_box), original);
	gtk_container_add(GTK_CONTAINER(button_box), espVertical);
	gtk_container_add(GTK_CONTAINER(button_box), espHorizontal);
	gtk_container_add(GTK_CONTAINER(button_box), cinza);
	gtk_container_add(GTK_CONTAINER(button_box), quantEntry);
	gtk_container_add(GTK_CONTAINER(button_box), quant);
	gtk_container_add(GTK_CONTAINER(button_box), salvar);
	gtk_container_add(GTK_CONTAINER(button_box), hist);
	gtk_container_add(GTK_CONTAINER(button_box), ajustarBEntry);
	gtk_container_add(GTK_CONTAINER(button_box), ajustarB);
	gtk_container_add(GTK_CONTAINER(button_box), ajustarCEntry);
	gtk_container_add(GTK_CONTAINER(button_box), ajustarC);
	gtk_container_add(GTK_CONTAINER(button_box), negativo);
	gtk_container_add(GTK_CONTAINER(button_box), equalizar);
	gtk_container_add(GTK_CONTAINER(button_box), matchingEntry);
	gtk_container_add(GTK_CONTAINER(button_box), matching);
	gtk_container_add(GTK_CONTAINER(button_box), sX);
	gtk_container_add(GTK_CONTAINER(button_box), sY);
	gtk_container_add(GTK_CONTAINER(button_box), zO);
	gtk_container_add(GTK_CONTAINER(button_box), zI);
	gtk_container_add(GTK_CONTAINER(button_box), gH);
	gtk_container_add(GTK_CONTAINER(button_box), gAH);
	gtk_container_add(GTK_CONTAINER(button_box), gauss);
	gtk_container_add(GTK_CONTAINER(button_box), lapla);
	gtk_container_add(GTK_CONTAINER(button_box), passaA);
	gtk_container_add(GTK_CONTAINER(button_box), PrewittHx);
	gtk_container_add(GTK_CONTAINER(button_box), PrewittHy);
	gtk_container_add(GTK_CONTAINER(button_box), sobelHx);
	gtk_container_add(GTK_CONTAINER(button_box), sobelHy);
			
	//variaveis passadas
	g_object_set_data(G_OBJECT(app), "Original", imgOriginal);
	g_object_set_data(G_OBJECT(app), "Alterada", imgAlterada);
	g_object_set_data(G_OBJECT(app), "Histograma", imgHistograma);
	g_object_set_data(G_OBJECT(app), "HistogramaAlterado", imgHistogramaAlterado);
	g_object_set_data(G_OBJECT(app), "Caminho", arqNome);
	g_object_set_data(G_OBJECT(app), "Quant", quantEntry);
	g_object_set_data(G_OBJECT(app), "Brilho", ajustarBEntry);
	g_object_set_data(G_OBJECT(app), "Contraste", ajustarCEntry);
	g_object_set_data(G_OBJECT(app), "MathingIMG", matchingEntry);
	g_object_set_data(G_OBJECT(app), "SX", sX);
	g_object_set_data(G_OBJECT(app), "SY", sY);
	
	//Função dos Botoes
	g_signal_connect(carregar, "clicked", G_CALLBACK(carregarImagem), app);
	g_signal_connect(original, "clicked", G_CALLBACK(recuperarOriginal), app);
	g_signal_connect(espVertical, "clicked", G_CALLBACK(espelharV), app);
	g_signal_connect(espHorizontal, "clicked", G_CALLBACK(espelharH), app);
	g_signal_connect(cinza, "clicked", G_CALLBACK(cinzaf), app);
	g_signal_connect(quant, "clicked", G_CALLBACK(quantf), app);
	g_signal_connect(salvar, "clicked", G_CALLBACK(salvarf), app);
	g_signal_connect(hist, "clicked", G_CALLBACK(histogramaf), app);
	g_signal_connect(ajustarB, "clicked", G_CALLBACK(ajustarBrilhof), app);
	g_signal_connect(ajustarC, "clicked", G_CALLBACK(ajustarContrastef), app);
	g_signal_connect(negativo, "clicked", G_CALLBACK(negativof), app);
	g_signal_connect(equalizar, "clicked", G_CALLBACK(equalizarf), app);
	g_signal_connect(matching, "clicked", G_CALLBACK(matchingf), app);
	g_signal_connect(zO, "clicked", G_CALLBACK(zoomOutf), app);
	g_signal_connect(zI, "clicked", G_CALLBACK(zoomInf), app);
	g_signal_connect(gH, "clicked", G_CALLBACK(ghf), app);
	g_signal_connect(gAH, "clicked", G_CALLBACK(gahf), app);
	g_signal_connect(gauss, "clicked", G_CALLBACK(gaussf), app);
	g_signal_connect(lapla, "clicked", G_CALLBACK(laplaf), app);
	g_signal_connect(passaA, "clicked", G_CALLBACK(passaAf), app);
	g_signal_connect(PrewittHx, "clicked", G_CALLBACK(PrewittHxf), app);
	g_signal_connect(PrewittHy, "clicked", G_CALLBACK(PrewittHyf), app);
	g_signal_connect(sobelHx, "clicked", G_CALLBACK(sobelHxf), app);
	g_signal_connect(sobelHy, "clicked", G_CALLBACK(sobelHyf), app);
	
	gtk_widget_show_all(window);
	gtk_widget_show_all(janelaOriginal);
	gtk_widget_show_all(janelaAlterada);
	gtk_widget_show_all(histograma);
}


int main(int argc, char **argv)
{
	
	GtkApplication *app;
	int status;
	
	app = gtk_application_new("org.gtk.programa", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	
	return status;
}
