// --------------------
//      Structure 
// --------------------

typedef struct Contact {
    char nom[31];
    char tel[11];
} Contact;

// --------------------
//      Prototypes 
// --------------------

void emptyBuffer(void);
void readChoice(int *p_choix, int nbChoix);
void readName(char *p_str);
void readTel(char *p_str);
int searchContactByName(int nbContacts, char nom[31], Contact t_contact[100]);
int searchContactByTel(int der, char tel[11], Contact t_contact[100]);
void deleteContactById(int id, int *p_nbContacts, Contact t_contact[100]);