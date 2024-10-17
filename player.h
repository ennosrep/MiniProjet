// --------------------
//      Prototypes 
// --------------------

void emptyBuffer(void);
void readChoice(int *p_choix);
void readName(char *p_str);
void readTel(char *p_str);
int searchContactByName(int der, char nom[31], char t_nom[100][31]);
int searchContactByTel(int der, char tel[11], char t_tel[100][11]);
void deleteContactById(int id, int *p_der, char t_nom[100][31], char t_tel[100][11]);
void showAllContacts(int der, char t_nom[100][31], char t_tel[100][11]);