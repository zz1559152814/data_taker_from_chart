void tools(void);

class Tools
{
public:	
	std::string Char_To_String(char *a);
	std::string ConstChar_To_String(const char *a);
	std::string G_filename(std::string proname);
	std::string int_to_string(int a);
	const char *String_To_ConstChar(std::string a);
};
const char *String_To_ConstChar(std::string a);