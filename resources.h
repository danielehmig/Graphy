#ifndef _RESOURCES_H_
#define _RESOURCES_H_

// Static identifiers for each GUI element used in the application
// These identifiers are used for event handling (i.e. so we know
// which element was clicked when the checkClick() returns true)

#define BUTTON 0x80000000

#define BUTTON1 (BUTTON | 0x00000001)
#define BUTTON2 (BUTTON | 0x00000002)
#define BUTTON3 (BUTTON | 0x00000004)
#define BUTTON4 (BUTTON | 0x00000008)
#define BUTTON5 (BUTTON | 0x00000010)
#define BUTTON6 (BUTTON | 0x00000020)
#define BUTTON7 (BUTTON | 0x00000040)

#define PANEL 0x40000000

#define PANEL1 (PANEL | 0x00000001)

#define EXPANDER 0x20000000

#define EXPANDER1 (EXPANDER | 0x00000001)

#endif