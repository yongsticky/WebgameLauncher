#pragma once


class CPngFileReader
{
public:
	CPngFileReader();
	~CPngFileReader();

	bool Load(const char* filePath);

	unsigned char* GetBGRA() const;

	int GetWidth() const;
	int GetHeight() const;
	int GetChannles() const;
	int GetBitDepth() const;
	int GetColorType() const;

private:
	unsigned char* m_bgra;
	int m_width;
	int m_height;
	int m_channels;
	int m_bit_depth;
	int m_color_type;
};