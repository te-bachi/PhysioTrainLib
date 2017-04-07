#ifndef __MENU_H__
#define __MENU_H__

/*
class Menu;
class MenuMain;
class MenuFile;
class MenuRun;

#include "CLI.h"
*/

class CLI;

class Menu {
    
    private:

    protected:
        CLI*                _cli;
    
    public:
                    
                            Menu();
                            Menu(CLI* cli);
        virtual             ~Menu();

        virtual bool        begin(CLI* cli);
        virtual void        listItems();
        virtual void        parse(char c);
};

class MenuMain : public Menu {
    
    private:
        const static char   MENU_FILE       = 'f';
        const static char   MENU_RUN        = 'r';
    
    public:
                    
                            MenuMain();
                            MenuMain(CLI* cli);
        virtual             ~MenuMain();

        virtual bool        begin(CLI* cli);
        virtual void        listItems();
        virtual void        parse(char c);
};

class MenuFile : public Menu {
    
    private:
        const static char   MENU_MAIN       = 'm';
        const static char   MENU_NEXT       = 'n';
    
    public:
                    
                            MenuFile();
                            MenuFile(CLI* cli);
        virtual             ~MenuFile();

        virtual bool        begin(CLI* cli);
        virtual void        listItems();
        virtual void        parse(char c);
};

class MenuRun : public Menu {
    
    private:
        const static char   MENU_START_STOP = 's';
        const static char   MENU_MAIN       = 'm';

        bool                _start;
    
    public:
                    
                            MenuRun();
                            MenuRun(CLI* cli);
        virtual             ~MenuRun();

        virtual bool        begin(CLI* cli);
        virtual void        listItems();
        virtual void        parse(char c);
};

#endif

