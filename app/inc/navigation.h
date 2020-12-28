/*
navigation.h
*/

//Struct

typedef struct Date{
  int year;
  int month;
  int day;
} Date;

typedef struct Search{
  int id_place;
  int nb_persons;
  int time_slot;
  Date date;
  int equipments[4];
  int drinks[2];
} Search;

typedef struct Calendar{
  int id_room;
  Date planning;
  Date date;
  int time_slot;

  GtkLabel *week;
  GtkButton *nav[2];
  GtkLabel *days[5];
  GtkButton *buttonsBooking[2][5];

  GtkLabel *room;
  GtkLabel *place;
  GtkLabel *dateLabel;
  GtkLabel *timeSlotLabel;
  GtkLabel *price;
  GtkImage *equipments[4];

} Calendar;


typedef struct Session{
  GtkBuilder *builder;
  GtkWindow *window;
  Search *search;
  Calendar *calendar;
  struct tm *today;
} Session;

typedef struct Booking{
  int idRoom;
  int nb_persons;
  double price;
  Date date;
  int drinks[2];
  int time_slot;
  Session *session;
} Booking;

typedef struct MysqlSelect{
  MYSQL *conn;
  char request[1024];
  MYSQL_RES *result;
} MysqlSelect;

typedef struct RoomGtkBox{
  GtkBuilder *builder;
  GtkBox *box;
  GtkLabel *locationLabel;
  GtkLabel *timeSlotLabel;
  GtkLabel *priceHalfDay;
  GtkLabel *nbPersons;
  GtkImage *equipments[4];
  GtkComboBoxText *bookingTimeSlotComboBox;
  GtkButton *bookingButton;
} RoomGtkBox;


void open_home_window(char *idWindow);

void click_button(Session *session, char *idButton,void (*function));
void close_and_open_window(Session *session, char *idNewWindow);
void newWindow(char* file, char* idWindow, Session *session);
void background_color( GtkWidget *widget, char *color );

//NAVIGATION
void open_reservations_window(GtkWidget *widget,gpointer data);
void open_new_res_window(GtkWidget *widget, gpointer data);
void open_place_room_window(GtkWidget *widget,gpointer data);
void open_equipment_window(Session *session);
void open_drink_window(Session *session);
void open_planning_window(Session *session);
void open_rooms_available_window(Session *session);
void open_drink_window_2(GtkWidget *Widget,gpointer data);
void open_reservations_window2(GtkWidget *widget,gpointer data);

// GET DATA
void getSearchArguments(GtkWidget *widget,gpointer data);
void getEquipmentsCheckbox(GtkWidget *widget,gpointer data);
void getDrinksCheckbox(GtkWidget *widget,gpointer data);
MysqlSelect findAvailableRooms(Search *search);
int *getRoomsEquipment(char *idRoom);
int isTimeSlotAvailable(char *time_slot, char *date, char *idRoom);
int isRestDayAvailable( Search *search, char *idRoom );
Booking *prepareBooking( Search *search, RoomGtkBox *room, char *idRoom );
int getPriceDrinks(Search *search);
void getIdRoom(GtkWidget *widget, gpointer data);
void getCalendarWidgets(Calendar *c, GtkBuilder *builder);
int *moveInCalendar(int year, int month, int day, int move);

// SET DATA
void fillComboBoxRooms(GtkComboBoxText *place,gpointer room);
RoomGtkBox *newRoomAvailable(MYSQL_ROW row);
void displayRoomEquipments(GtkImage *equipments[4], char *idRoom);
void displayTimeSlotComboBox(RoomGtkBox *room, char *idRoom, Search *search);
void displayTimeSlotLabel(RoomGtkBox *room, char *idRoom, Search *search);
void reserveRoom(GtkWidget *widget, gpointer data);
void planningNumbers(Calendar *calendar, struct tm *date);
void click_button_planning(Session *session, char *idButton);
void updatePlanningNumbers(int *startDate, GtkLabel *days[5]);
void planningChangeWeek(GtkWidget *widget, gpointer data);
void updateWeekLabel( int *startDate, GtkLabel *week);
void setRoomInfo(Calendar *calendar);
void updateButtonsPlanning(Calendar *calendar);


// PRINT
void printSearchParameter(Search *seach);

//STYLE
void stylePlanningRoom(Session *session);




//
