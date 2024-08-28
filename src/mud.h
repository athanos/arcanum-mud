/*
 * This is the main headerfile
 */

#ifndef MUD_H
#define MUD_H

#include <zlib.h>
#include <pthread.h>
#include <arpa/telnet.h>

#include "list.h"
#include "stack.h"

/************************
 * Standard definitions *
 ************************/

/* define TRUE and FALSE */
#ifndef FALSE
#define FALSE   0
#endif
#ifndef TRUE
#define TRUE    1
#endif

#define eTHIN   0
#define eBOLD   1

/* A few globals */
#define PULSES_PER_SECOND     5                   /* must divide 1000 : 4, 5 or 8 works */
#define MAX_BUFFER         32768                  /* seems like a decent amount         */
#define MAX_OUTPUT         32768                  /* well shoot me if it isn't enough   */
#define MAX_HELP_ENTRY     32768                  /* roughly 40 lines of blocktext      */
#define MAX_KEY_HASH       1024
#define MUDPORT            1801                   /* just set whatever port you want    */
#define FILE_TERMINATOR    "EOF"                  /* end of file marker                 */
#define COPYOVER_FILE      "../txt/copyover.dat"  /* tempfile to store copyover data    */
#define EXE_FILE           "../src/arcanum"     /* the name of the mud binary         */

#define MAX_STRING_LENGTH  8192
#define MAX_INPUT_LENGTH   1024
#define MSL MAX_STRING_LENGTH
#define MIL MAX_INPUT_LENGTH




#define CLEAR_SCREEN	   "\033[H\033[J"

/* Connection states */
#define STATE_NEW_NAME         0
#define STATE_NEW_PASSWORD     1
#define STATE_VERIFY_PASSWORD  2
#define STATE_ASK_PASSWORD     3
#define STATE_ASK_GENDER       4
#define STATE_ASK_RACE	       5
#define STATE_INTO_GAME	       6
#define STATE_PLAYING          7
#define STATE_CLOSED           8

/* Thread states - please do not change the order of these states    */
#define TSTATE_LOOKUP          0  /* Socket is in host_lookup        */
#define TSTATE_DONE            1  /* The lookup is done.             */
#define TSTATE_WAIT            2  /* Closed while in thread.         */
#define TSTATE_CLOSED          3  /* Closed, ready to be recycled.   */

/* player levels */
#define LEVEL_GUEST            1  /* Dead players and actual guests  */
#define LEVEL_PLAYER           2  /* Almost everyone is this level   */
#define LEVEL_ADMIN            3  /* Any admin without shell access  */
#define LEVEL_GOD              4  /* Any admin with shell access     */

/* Communication Ranges */
#define COMM_LOCAL             0  /* same room only                  */
#define COMM_LOG              10  /* admins only                     */

/* Gender Defines */
#define GENDER_MALE	 0
#define GENDER_FEMALE	 1
#define GENDER_NB	 2
#define GENDER_MAX	 3

/* Race Defines */
#define RACE_CENTAUR	 0
#define RACE_DRUAS	 1
#define RACE_DWARF	 2
#define RACE_ELF	 3
#define RACE_FERRAN	 4
#define RACE_GNOME	 5
#define RACE_HUMAN	 6
#define RACE_KOBOLD	 7
#define RACE_OGRE	 8
#define RACE_ORC	 9
#define RACE_RAKASHAN	10
#define RACE_SAURIAN	11
#define RACE_WOLFEN	12
#define RACE_MAX	13

/* Stat Defines */
#define STAT_STRENGTH		 0
#define STAT_AGILITY		 1
#define STAT_ENDURANCE		 2
#define STAT_VITALITY		 3
#define STAT_INTELLIGENCE	 4
#define STAT_PERCEPTION		 5
#define STAT_WILLPOWER		 6
#define STAT_CHARISMA		 7
#define STAT_HIT_POINTS		 8
#define STAT_STAMINA		 9
#define STAT_MANA		10
#define STAT_DEFENSE		11
#define STAT_RESISTANCE		12
#define STAT_ATTACK		13
#define STAT_SPELL_POWER	14
#define STAT_INITIATIVE		15
#define STAT_RANGE		16
#define STAT_MORALE		17
#define STAT_SKILL_POINTS	18
#define STAT_CAPACITY		19
#define STAT_MAX		20

/* Skill Defines */
	//Science Skills
#define SK_ANALYZE_MIXTURE		  0
#define SK_ANCIENT_LORE			  1
#define SK_ART				  2
#define SK_CARTOGRAPHY			  3
#define SK_CHIROGRAPHY			  4
#define SK_DIPLOMACY			  5
#define SK_DRAFTING			  6
#define SK_HEALING_ARTS			  7
#define SK_HORTICULTURE			  8
#define SK_INTERNAL_ALCHEMY		  9
#define SK_INVENTING			 10
#define SK_LINGUISTICS			 11
#define SK_MUSIC			 12
#define SK_NATURALISM			 13
#define SK_NAVIGATION			 14
#define SK_READ_MAGIC			 15
#define SK_THEOLOGY			 16
	//Background Skills
#define SK_BARTER			 17
#define SK_BASIC_SEAMANSHIP		 18
#define SK_CRAFT_BREWING		 19
#define SK_CRAFT_COOKING		 20
#define SK_CRAFT_LEATHER_WORKING	 21
#define SK_CRAFT_WOOD_WORKING		 22
#define SK_CRAFT_ARMOR_SMITHING		 23
#define SK_CRAFT_WEAPON_SMITHING	 24
#define SK_CRAFT_GARDENING		 25
#define SK_CRAFT_MASONRY		 26
#define SK_KNOWLEDGE_GENERAL_LORE	 27
#define SK_KNOWLEDGE_NATURE		 28
#define SK_KNOWLEDGE_RELIGIOUS_LORE	 29
#define SK_KNOWLEDGE_ARCANE_LORE	 30
#define SK_KNOWLEDGE_DEMON_LORE	 	 31
#define SK_KNOWLEDGE_GEOGRAPHY		 32
#define SK_KNOWLEDGE_HISTORY		 33
#define SK_KNOWLEDGE_DIVINE_LORE	 34
#define SK_DRINKING			 35
#define SK_GAMBLING			 36
#define SK_HAGGLING			 37
#define SK_LANGUAGE_CENTAUR		 38
#define SK_LANGUAGE_COMMON		 39
#define SK_LANGUAGE_DRUAS		 40
#define SK_LANGUAGE_DWARF		 41
#define SK_LANGUAGE_ELF			 42
#define SK_LANGUAGE_FERRAN		 43
#define SK_LANGUAGE_GNOME		 44
#define SK_LANGUAGE_HUMAN		 45
#define SK_LANGUAGE_KOBOLD		 46
#define SK_LANGUAGE_OGRE		 47
#define SK_LANGUAGE_ORC			 48
#define SK_LANGUAGE_RAKASHAN		 49
#define SK_LANGUAGE_SAURIAN		 50
#define SK_LANGUAGE_WOLFEN		 51
#define SK_LITERACY_CENTAUR              52
#define SK_LITERACY_COMMON               53
#define SK_LITERACY_DRUAS                54
#define SK_LITERACY_DWARF                55
#define SK_LITERACY_ELF                  56
#define SK_LITERACY_FERRAN               57
#define SK_LITERACY_GNOME                58
#define SK_LITERACY_HUMAN                59
#define SK_LITERACY_KOBOLD               60
#define SK_LITERACY_OGRE                 61
#define SK_LITERACY_ORC                  62
#define SK_LITERACY_RAKASHAN             63
#define SK_LITERACY_SAURIAN              64
#define SK_LITERACY_WOLFEN               65
#define SK_RIDING			 66
#define SK_SIGN				 67
#define SK_STREETWISE			 68
#define SK_SWIMMING			 69
	//Combat Skills
#define SK_ARCHERY_I			 70
#define SK_ARCHERY_II			 71
#define SK_BLIND_FIGHTING		 72
#define SK_COMMAND			 73
#define SK_MARTIAL_ARTS_I		 74
#define SK_MARTIAL_ARTS_II		 75
#define SK_MOUNTED_COMBAT_I		 76
#define SK_MOUNTED_COMBAT_II		 77
#define SK_STREET_FIGHTING		 78
#define SK_WEAPON_PROF_BLOWGUN		 79
#define SK_WEAPON_PROF_BLUNT		 80
#define SK_WEAPON_PROF_BOW		 81
#define SK_WEAPON_PROF_CHAIN		 82
#define SK_WEAPON_PROF_DAGGER_KNIFE	 83
#define SK_WEAPON_PROF_FORKED_TRIDENT	 84
#define SK_WEAPON_PROF_GRAPPLING_HOOK	 85
#define SK_WEAPON_PROF_MISSILE_WEAPONS	 86
#define SK_WEAPON_PROF_NET		 87
#define SK_WEAPON_PROF_PAIRED_WEAPONS 	 88
#define SK_WEAPON_PROF_SHIELD		 89
#define SK_WEAPON_PROF_SIEGE_WEAPONS	 90
#define SK_WEAPON_PROF_SPEAR		 91
#define SK_WEAPON_PROF_STAFF		 92
#define SK_WEAPON_PROF_SWORD		 93
#define SK_WEAPON_PROF_THROWING_WEAPONS	 94
#define SK_WEAPON_PROF_WHIP		 95
#define SK_WEAPON_SPEC_BLOWGUN           96
#define SK_WEAPON_SPEC_BLUNT             97
#define SK_WEAPON_SPEC_BOW               98
#define SK_WEAPON_SPEC_CHAIN             99
#define SK_WEAPON_SPEC_DAGGER_KNIFE     100
#define SK_WEAPON_SPEC_FORKED_TRIDENT   101
#define SK_WEAPON_SPEC_GRAPPLING_HOOK   102
#define SK_WEAPON_SPEC_MISSILE_WEAPONS  103
#define SK_WEAPON_SPEC_NET              104
#define SK_WEAPON_SPEC_PAIRED_WEAPONS   105
#define SK_WEAPON_SPEC_SHIELD           106
#define SK_WEAPON_SPEC_SIEGE_WEAPONS    107
#define SK_WEAPON_SPEC_SPEAR            108
#define SK_WEAPON_SPEC_STAFF            109
#define SK_WEAPON_SPEC_SWORD            110
#define SK_WEAPON_SPEC_THROWING_WEAPONS 111
#define SK_WEAPON_SPEC_WHIP             112
#define SK_WRESTLING			113
#define SK_ZEN_ARCHERY			114
	//Common Skills
#define SK_BRAWLING			115
#define SK_CLIMBING			116
#define SK_FLOATING			117
#define SK_HIDING			118
#define SK_LEAPING			119
#define SK_MOVE_SILENTLY		120
#define SK_SEARCHING			121
	//Performing Skills
#define SK_ACROBATICS_I			122
#define SK_ACROBATICS_II		123
#define SK_ACTING			124
#define SK_ANIIMAL_TRAINING		125
#define SK_JUGGLING			126
#define SK_KNIFE_THROWING		127
#define SK_LEGERDEMAIN			128
#define SK_ORATORY			129
#define SK_SIDE_SHOW_TALENT		130
	//Special Skills
#define SK_ADV_ALCHEMICAL_EQUIPMENT	131
#define SK_ADV_ALCHEMICAL_SUBSTANCES	132
#define SK_ADV_NECROMANTIC_RITUALS	133
#define SK_ADV_THAUMATURGICAL_EQUIPMENT	134
#define SK_ALCHEMICAL_DEVICES		135
#define SK_ALCHEMICAL_DUSTS		136
#define SK_AQUA_VITAE_AND_HOMUNCULI	137
#define SK_ARMORED_SPELL_CASTING	138
#define SK_ARTIST			139
#define SK_ASSASSINATE			140
#define SK_BACKSTAB			141
#define SK_CONVERT			142
#define SK_DETECT_CONJURATION		143
#define SK_DETECT_ILLUSION		144
#define SK_ESSENCES			145
#define SK_EVOKER			146
#define SK_GOLEMS			147
#define SK_GREATER_MAGIC_ITEMS		148
#define SK_HERBAL_ELIXERS		149
#define SK_HERBAL_REMEDIES		150
#define SK_HOLY_ITEMS			151
#define SK_INFLUENCE_ANIMALS		152
#define SK_INSCRIBE_SYMBOL		153
#define SK_JACK_OF_ALL_TRADES		154
#define SK_LOCATE_RARE_EARTHS		155
#define SK_MACHINA			156
#define SK_MAGICAL_MIXTURES		157
#define SK_MAGICAL_WEAPONS_AND_ARMOR	158
#define SK_MANY_MASKS			159
#define SK_MINOR_MAGIC_ITEMS		160
#define SK_MUSCIAN			161
#define SK_NECROMANTIC_RITUALS		162
#define SK_OBSERVATORY			163
#define SK_PASS_WITHOUT_TRACE		164
#define SK_PATRON_OF_THE_LOWER_PLANES	165
#define SK_PHILTRES			166
#define SK_POTIONS			167
#define SK_POWER_ANIMAL			168
#define SK_PROJECTION_OF_WILL		169
#define SK_RODS_STAVES_WANDS		170
#define SK_RUNES			171
#define SK_SCHOLARLY			172
#define SK_SCROLLS			173
#define SK_SEE_INTO_SPIRIT_REALM	174
#define SK_SHAPE_CHANGE_ANIMAL		175
#define SK_SPELL_CAST_ASTROLOGY		176
#define SK_SPELL_CAST_BLACK_MAGIC	177
#define SK_SPELL_CAST_DIVINE_MAGIC	178
#define SK_SPELL_CAST_ELEMENTAL_MAGIC	179
#define SK_SPELL_CAST_ENCHANTMENT	180
#define SK_SPELL_CAST_HIGH_MAGIC	181
#define SK_SPELL_CAST_LOW_MAGIC		182
#define SK_SPELL_CAST_MYSTICISM		183
#define SK_SPELL_CAST_SORCERY		184
#define SK_SPIRIT_BINDING		185
#define SK_TOXIC_POWDERS		186
#define SK_TURN_UNDEAD			187
#define SK_VENOMS_AND_POISONS		188
#define SK_WAYLAY			189
	//Thieving Skills
#define SK_APPRAISE_TREASURE		190
#define SK_CATWALK			191
#define SK_CON				192
#define SK_DECIPHER			193
#define SK_EVADE_PURSUIT		194
#define SK_FORGERY			195
#define SK_HIDE_IN_SHADOWS		196
#define SK_INFILTRATE			197
#define SK_INTERROGATE			198
#define SK_LIP_READING			199
#define SK_LOCK_PICKING			200
#define SK_PICK_POCKET			201
#define SK_SCALING_WALLS		202
#define SK_STEALTH			203
#define SK_TAILING			204
#define SK_THIEVES_CANT			205
#define SK_TRAPS			206
	//Woodlore Skills
#define SK_CAMOUFLAGE			207
#define SK_HERB_LORE			208
#define SK_HUNTING			209
#define SK_MOUNTAIN_CLIMBING		210
#define SK_READ_TRACKS			211
#define SK_SCOUTING			212
#define SK_SNARES			213
#define SK_STALKING			214
#define SK_SURVIVAL			215
#define SK_TRACKING			216

#define SKILL_MAX			217

/* define simple types */
typedef  unsigned char     bool;
typedef  short int         sh_int;


/******************************
 * End of standard definitons *
 ******************************/

/***********************
 * Defintion of Macros *
 ***********************/

#define LOWER(c)        ((c) >= 'A' && (c) <= 'Z' ? (c)+'a'-'A' : (c))
#define UPPER(c)        ((c) >= 'a' && (c) <= 'z' ? (c)+'A'-'a' : (c))
#define UMIN(a, b)		((a) < (b) ? (a) : (b))
#define UMAX(a, b)              ((a) > (b) ? (a) : (b))
#define URANGE(a, b, c)        ((b) < (a) ? (a) : ((b) > (c) ? (c) : (b)))
#define IS_ADMIN(ch)          ((ch->level) > LEVEL_PLAYER ? TRUE : FALSE)
#define IREAD(sKey, sPtr)             \
{                                     \
  if (!strcasecmp(sKey, word))        \
  {                                   \
    int sValue = fread_number(fp);    \
    sPtr = sValue;                    \
    found = TRUE;                     \
    break;                            \
  }                                   \
}
#define SREAD(sKey, sPtr)             \
{                                     \
  if (!strcasecmp(sKey, word))        \
  {                                   \
    sPtr = fread_string(fp);          \
    found = TRUE;                     \
    break;                            \
  }                                   \
}
#define SKREAD(sKey, dMob)                   \
{                                           \
    if (compares(sKey, word))               \
    {                                       \
        int value   = fread_number(fp);     \
        char * temp = fread_word(fp);       \
        int sn      = find_skill(temp);     \
        if (sn < 0)                         \
        {                                   \
            log_string("load_player: SKREAD unknown skill %s", temp); \
            log_string("load_player: SKREAD unknown skill %s", temp); \
        }                                   \
        else                                \
            dMob->skills[sn] = value;       \
        found = TRUE;                       \
        break;                              \
    }                                       \
}

/***********************
 * End of Macros       *
 ***********************/


/******************************
 * Bit flag Support           *
 ******************************/
#define IS_SET(flag, bit)       ((flag) & (bit))
#define SET_BIT(var, bit)       ((var) |= (bit))
#define REMOVE_BIT(var, bit)    ((var) &= ~(bit))
#define TOGGLE_BIT(var, bit)    ((var) ^= (bit))
/* Easy reading */
#define A                       0x1
#define B                       0x2
#define C                       0x4
#define D                       0x8
#define E                       0x10
#define F                       0x20
#define G                       0x40
#define H                       0x80
#define I                       0x100
#define J                       0x200
#define K                       0x400
#define L                       0x800
#define M                       0x1000
#define N                       0x2000
#define O                       0x4000
#define P                       0x8000
#define Q                       0x10000
#define R                       0x20000
#define S                       0x40000
#define T                       0x80000
#define U                       0x100000
#define V                       0x200000
#define W                       0x400000
#define X                       0x800000
#define Y                       0x1000000
#define Z                       0x2000000
#define aa			0x8000000
#define bb			0x10000000
#define cc			0x20000000
#define dd			0x40000000
#define ee			0x80000000

/******************************
 * New structures             *
 ******************************/

/* type defintions */
typedef struct  dSocket       D_SOCKET;
typedef struct  char_data     CHAR_DATA;
typedef struct  help_data     HELP_DATA;
typedef struct  lookup_data   LOOKUP_DATA;
typedef struct  event_data    EVENT_DATA;
typedef struct  skill_data    SKILL_DATA;
typedef struct  race_data     RACE_DATA;

/* the actual structures */
struct dSocket
{
  CHAR_DATA     * player;
  CHAR_DATA     * original;
  LIST          * events;
  char          * hostname;
  char            inbuf[MAX_BUFFER];
  char		  incomm[MAX_INPUT_LENGTH];
  char		  inlast[MAX_INPUT_LENGTH];
  char            outbuf[MAX_OUTPUT];
  int		  outsize;
  int		  outtop;
  char            next_command[MAX_BUFFER];
  bool            bust_prompt;
  sh_int          lookup_status;
  sh_int          state;
  sh_int          control;
  sh_int          top_output;
  unsigned char   compressing;                 /* MCCP support */
  z_stream      * out_compress;                /* MCCP support */
  unsigned char * out_compress_buf;            /* MCCP support */
  char		* showstr_head;
  char		* showstr_points;
  void		* pEdit;          // OLC
  char		**pString;        // OLC
  int		  editor;	  // OLC
};

struct char_data
{
  //Shared data for PC and NPC
  D_SOCKET      * socket;
  LIST          * events;
  char          * name;
  char          * password;
  sh_int          level;
  sh_int	  gender;
  sh_int	  race;
  sh_int	  stat_base[STAT_MAX];
  sh_int	  stat_curr[STAT_MAX];
  sh_int	  skills[SKILL_MAX];
  sh_int	  skills_t[SKILL_MAX];
};

struct race_data {
  char		*name;
};

struct skill_data {
  sh_int	 skill_number;
  char		*name;
  sh_int	 pre_req;
//  sh_int	 stat_modifier;
};

struct help_data
{
  time_t          load_time;
  char          * keyword;
  char          * text;
};

struct lookup_data
{
  D_SOCKET       * dsock;   /* the socket we wish to do a hostlookup on */
  char           * buf;     /* the buffer it should be stored in        */
};

struct typCmd
{
  char      * cmd_name;
  void     (* cmd_funct)(CHAR_DATA *ch, char *arg);
  sh_int      level;
};

typedef struct buffer_type
{
  char   * data;        /* The data                      */
  int      len;         /* The current len of the buffer */
  int      size;        /* The allocated size of data    */
} BUFFER;


/* here we include external structure headers */
#include "event.h"

/******************************
 * End of new structures      *
 ******************************/

/***************************
 * Global Variables        *
 ***************************/

extern  STACK       *   dsock_free;       /* the socket free list               */
extern  LIST        *   dsock_list;       /* the linked list of active sockets  */
extern  STACK       *   char_free;     /* the char free list               */
extern  LIST        *   char_list;     /* the char list of active chars  */
extern  LIST        *   help_list;        /* the linked list of help files      */
extern  const struct    typCmd tabCmd[];  /* the command table                  */
extern  bool            shut_down;        /* used for shutdown                  */
extern  char        *   greeting;         /* the welcome greeting               */
extern  char        *   motd;             /* the MOTD help file                 */
extern  int             control;          /* boot control socket thingy         */
extern  time_t          current_time;     /* let's cut down on calls to time()  */

extern int log_index;

/*************************** 
 * End of Global Variables *
 ***************************/

/***********************
 *    MCCP support     *
 ***********************/

extern const unsigned char compress_will[];
extern const unsigned char compress_will2[];

#define TELOPT_COMPRESS       85
#define TELOPT_COMPRESS2      86
#define COMPRESS_BUF_SIZE   8192

/***********************
 * End of MCCP support *
 ***********************/

/***********************************
 * Prototype function declerations *
 ***********************************/

/* more compact */
#define  D_S         D_SOCKET
#define  C_D         CHAR_DATA

#define  buffer_new(size)             __buffer_new     ( size)
#define  buffer_strcat(buffer,text)   __buffer_strcat  ( buffer, text )

char  *crypt                  ( const char *key, const char *salt );

/*
 * db.c
 */
void area_update (void);

/*
 * socket.c
 */
int   init_socket             ( void );
bool  new_socket              ( int sock );
void  close_socket            ( D_S *dsock, bool reconnect );
bool  read_from_socket        ( D_S *dsock );
bool  text_to_socket          ( D_S *dsock, const char *txt );  /* sends the output directly */
void  text_to_buffer          ( D_S *dsock, const char *txt );  /* buffers the output        */
void  text_to_char          ( C_D *ch, const char *txt );   /* buffers the output        */
void  next_cmd_from_buffer    ( D_S *dsock );
bool  flush_output            ( D_S *dsock );
void  handle_new_connections  ( D_S *dsock, char *arg );
void  clear_socket            ( D_S *sock_new, int sock );
void  recycle_sockets         ( void );
void *lookup_address          ( void *arg );

/*
 * interpret.c
 */
void  handle_cmd_input        ( D_S *dsock, char *arg );

/*
 * io.c
 */
void    log_string            ( const char *txt, ... );
void    bug                   ( const char *txt, ... );
time_t  last_modified         ( char *helpfile );
char   *read_help_entry       ( const char *helpfile );     /* pointer         */
char   *fread_line            ( FILE *fp );                 /* pointer         */
char   *fread_string          ( FILE *fp );                 /* allocated data  */
char   *fread_word            ( FILE *fp );                 /* pointer         */
int     fread_number          ( FILE *fp );                 /* just an integer */

/* 
 * strings.c
 */
char   *one_arg               ( char *fStr, char *bStr );
char   *strdup                ( const char *s );
int     strcasecmp            ( const char *s1, const char *s2 );
bool    is_prefix             ( const char *aStr, const char *bStr );
char   *capitalize            ( char *txt );
BUFFER *__buffer_new          ( int size );
void    __buffer_strcat       ( BUFFER *buffer, const char *text );
void    buffer_free           ( BUFFER *buffer );
void    buffer_clear          ( BUFFER *buffer );
int     bprintf               ( BUFFER *buffer, char *fmt, ... );
bool compares(const char *aStr, const char *bStr);

/*
 * help.c
 */
bool  check_help              ( C_D *ch, char *helpfile );
void  load_helps              ( void );

/*
 * utils.c
 */
bool  check_name              ( const char *name );
void  clear_char            ( C_D *ch );
void  free_char             ( C_D *ch );
void  communicate             ( C_D *ch, char *txt, int range );
void  load_muddata            ( bool fCopyOver );
char *get_time                ( void );
void  copyover_recover        ( void );
C_D  *check_reconnect         ( char *player );
int   rand_number(int min, int max);
long  randneg                 (long start, long end);
long  dice                    (long howmany, long type);
long  percent                 (void);

/*
 * action_safe.c
 */
void  cmd_say                 ( C_D *ch, char *arg );
void  cmd_quit                ( C_D *ch, char *arg );
void  cmd_shutdown            ( C_D *ch, char *arg );
void  cmd_commands            ( C_D *ch, char *arg );
void  cmd_who                 ( C_D *ch, char *arg );
void  cmd_help                ( C_D *ch, char *arg );
void  cmd_compress            ( C_D *ch, char *arg );
void  cmd_save                ( C_D *ch, char *arg );
void  cmd_copyover            ( C_D *ch, char *arg );
void  cmd_linkdead            ( C_D *ch, char *arg );

/*
 * mccp.c
 */
bool  compressStart           ( D_S *dsock, unsigned char teleopt );
bool  compressEnd             ( D_S *dsock, unsigned char teleopt, bool forced );

/*
 * save.c
 */
void  save_player             ( C_D *ch );
C_D  *load_player             ( char *player );
C_D  *load_profile            ( char *player );

/*
 * color.c
 */
int substitute_color(char *input, char *output, int colors);

/*
 * skills.c
 */
extern const struct skill_data skill_table[];
int find_skill(const char *name);

/*******************************
 * End of prototype declartion *
 *******************************/

#endif  /* MUD_H */
