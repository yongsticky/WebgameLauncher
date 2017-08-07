#include "stdafx.h"
#include "PngFileReader.h"

#include "png.h"
#include "zlib.h"


CPngFileReader::CPngFileReader()
{
}


CPngFileReader::~CPngFileReader()
{
}

bool CPngFileReader::Load(const char* filePath)
{
	// 打开文件
	png_FILE_p fp_png = fopen(filePath, "rb");
	if (fp_png == NULL)
	{
		return false;
	}

	// 初始化
	png_structp read_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (read_ptr == NULL)
	{
		return false;
	}
	
	png_infop info_ptr = png_create_info_struct(read_ptr);
	if (info_ptr == NULL)
	{
		return false;
	}
			
	// 检测是否PNG文件
	setjmp(png_jmpbuf(read_ptr));
	png_byte buf[4];
	int tmp = fread((void*)buf, 1, 4, fp_png);	
	tmp = png_sig_cmp(buf, (png_size_t)0, 4);
	if (tmp != 0)
	{
		return false;
	}
	
	// 读取文件
	rewind(fp_png);
	png_init_io(read_ptr, fp_png);	
	png_read_png(read_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

	// 获取通道，色深，颜色类型
	m_channels = png_get_channels(read_ptr, info_ptr);
	m_bit_depth = png_get_bit_depth(read_ptr, info_ptr);
	m_color_type = png_get_color_type(read_ptr, info_ptr);
	m_width = png_get_image_width(read_ptr, info_ptr);
	m_height = png_get_image_height(read_ptr, info_ptr);

	// 	读取像素
	png_bytep* row_ptrs = png_get_rows(read_ptr, info_ptr);	
	if (m_channels == 4 || m_color_type == PNG_COLOR_TYPE_RGB_ALPHA)
	{		
		int size = (m_width*m_height*4*sizeof(unsigned char));

		m_bgra = (unsigned char*)malloc(size);
		if (m_bgra)
		{
			int cur_pos = 0;
			for (int i = 0; i < m_height; i++)
			{
				for (int j = 0; j < 4*m_width; )
				{
					m_bgra[cur_pos++] = row_ptrs[i][j+2];		// b
					m_bgra[cur_pos++] = row_ptrs[i][j+1];		// g
					m_bgra[cur_pos++] = row_ptrs[i][j];			// r
					m_bgra[cur_pos++] = row_ptrs[i][j+3];		// a
															
					j += 4;
				}
			}
			
			png_destroy_read_struct(&read_ptr, &info_ptr, 0);
			fclose(fp_png);

			return true;
		}
	}
	
	png_destroy_read_struct(&read_ptr, &info_ptr, 0);
	fclose(fp_png);

	return false;
}

unsigned char* CPngFileReader::GetBGRA() const
{
	return m_bgra;
}

int CPngFileReader::GetWidth() const
{
	return m_width;
}

int CPngFileReader::GetHeight() const
{
	return m_height;
}

int CPngFileReader::GetChannles() const
{
	return m_channels;
}

int CPngFileReader::GetBitDepth() const
{
	return m_bit_depth;
}

int CPngFileReader::GetColorType() const
{
	return m_color_type;
}