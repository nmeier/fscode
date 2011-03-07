
typedef void (*registry_op)(const char* psection, const char* key, float* pvalue);

void pdfview_remember(char* section, RECT* rect);
bool pdfview_recall(char* section, RECT* rect);
void pdfview_remember(char* section, char* key, float value);
float pdfview_recall(char* section, char* key, float fallback);

HWND pdfview_init(HWND hParent, char* ptitle, char* ppagetitle);
void toggle_pdfview();
void set_wheel_modifiers(int vkpage, int vkzoom, int vkrotate);
void pdfview_show();
void pdfview_hide();
bool pdfview_visible();
void open_document();
void open_document(const char* pfile);
int count_documents();
void prev_document();
void next_document();
void goto_page(int page);
void prev_page();
void next_page();
void zoom_in();
void zoom_out();
void zoom_100();
void close_document();
void close_all_documents();

