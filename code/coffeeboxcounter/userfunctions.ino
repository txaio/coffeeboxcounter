// USERS
#define NUM_USERS 5
// Struct to define user structure
typedef struct {
		byte uid[4];             //4 Bytes - UID to compare RFID respons
    char name[4];               // 4 Bytes - User abreviation i.e: David - DAV
    unsigned int current_total; // 2 Bytes - Current user's coffee consumed
    unsigned int backup_total;  // 2 Bytes - Backup of the user's cofee consumption before last reset
} user; // TOTAL 12 Bytes (42 Users in 512 B EPROM)

//user users [X]; X Max 42 Users

// Test Users
user users [NUM_USERS] = {
  {{0xFF,0xFF,0xEE,0x00},"THI",11,10},
  {{0xAA,0xBB,0xCC,0x0A},"MAR",2,98},
  {{0xCC,0xEE,0xDD,0xDD},"MAN",121,221},
  {{0x01,0x22,0x33,0xFF},"ERI",59,300},
  {{0x01,0x22,0x33,0xFF},"ROB",333,109}
};
