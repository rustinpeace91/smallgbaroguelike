// constants.h

#ifndef DUMMY_DATA_H
#define DUMMY_DATA_H
namespace DummyData {
    constexpr int ARRAY_SIZE = 4;   // Adjust the size as needed
    inline const char* MAIN_MENU_OPTIONS[ARRAY_SIZE] = {
        "Inventory", "Magic", "Equipment", "Options"
    };
    inline const char* INVENTORY[10] = {
        "hlth ptn",
        "hlth ptn",
        "irn swd",
        "mag crst",
        "irn hlmt",
        "irn shld",
        "irn bst",
        "irn pnt",
        "turkey",
        "rat tail"
  };

};
#endif
