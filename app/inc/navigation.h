/*
navigation.h
*/

//Struct

typedef struct Date{
  int year;
  int month;
  int day;
} Date;

typedef struct RoomGtkBox{
  GtkBox *box;
  GtkBuilder *builder;
  GtkLabel *locationLabel;
  GtkLabel *timeSlotLabel;
  GtkLabel *priceHalfDay;
  GtkLabel *nbPersons;
  GtkImage *equipments[4];
  GtkComboBoxText *bookingTimeSlotComboBox;
  GtkButton *bookingButton;
} RoomGtkBox;

typedef struct Booking{
  char test[8];
  int idRoom;
  int nb_persons;
  double price;
  Date date;
  int drinks[2];
  int time_slot;
  void *session;
  struct Booking *next;
} Booking;


typedef struct Search{
  int id_place;
  int nb_persons;
  int time_slot;
  Date date;
  int equipments[4];
  int drinks[2];
  Booking *startBooking;
} Search;

typedef struct Calendar{
  int id_room;
  int id_place;
  Date planning;
  Date daySelected;
  int timeSlotSelected;
  int wDaySelected;
  int drinks[2];

  GtkLabel *week;
  GtkLabel *days[5];
  GtkButton *buttonsBooking[2][5];
  GtkLabel *room;
  GtkLabel *place;
  GtkLabel *dateLabel;
  GtkLabel *timeSlotLabel;
  GtkLabel *price;
  GtkImage *equipments[4];
  GtkComboBoxText *timeSlotCombo;
  GtkButton *next;
} Calendar;

typedef struct MysqlSelect{
  MYSQL *conn;
  char request[1024];
  MYSQL_RES *result;
} MysqlSelect;

typedef struct ReservationBox{
  GtkBox *box;
  GtkLabel *locationLabel;
  GtkLabel *dateLabel;
  GtkLabel *timeSlotLabel;
  GtkLabel *priceLabel;
  GtkImage *equipments[4];
  GtkImage *drinks[2];
  GtkButton *delete;
} ReservationBox;

typedef struct delReservation{
  uint32_t idBooking;
  GtkWidget *dialogWindow;
  void *session;
  struct delReservation *next;
}delReservation;

typedef struct Session{
  GtkBuilder *builder;
  GtkWindow *window;
  Search *search;
  Calendar *calendar;
  struct tm *today;
  struct delReservation *nextReservation;
  void (*backFunction)(GtkWidget *, gpointer);
} Session;



Session *initSession();
void kamajiQuit(GtkWidget *w, gpointer data);

// free
void freeBookings(Booking **start);
void freeDelReservations(delReservation **start);
void freeCheckDataSearch(GtkWidget *widget,gpointer data);

void click_button(Session *session, char *idButton,void (*function));
void close_and_open_window(Session *session, char *idNewWindow);
void newWindow(char* file, char* idWindow, Session *session);
void background_color( GtkWidget *widget, char *color );

//NAVIGATION
void open_home_window(GtkWidget *widget, gpointer data);
void open_reservations_window(GtkWidget *widget, gpointer data);
void open_new_res_window(GtkWidget *widget, gpointer data);
void open_place_room_window(GtkWidget *widget, gpointer data);
void open_equipment_window(GtkWidget *widget, gpointer data);
void open_drink_window(GtkWidget *widget, gpointer data);
void open_planning_window(GtkWidget *widget,gpointer data);
void open_rooms_available_window(GtkWidget *widget, gpointer data);
void open_drink_window_2(GtkWidget *Widget,gpointer data);
void open_reservations_window2(GtkWidget *widget,gpointer data);
void editReservation(GtkWidget *widget,gpointer data);


// BACK
void back(GtkWidget *widget, gpointer data);

// GET DATA
void getSearchArguments(GtkWidget *widget, Session *session);
void getEquipmentsCheckbox(GtkWidget *widget, Session *session);
void getSearchDrinksCheckbox(GtkWidget *widget, Session *session);
MysqlSelect findAvailableRooms(Search *search);
int *getRoomsEquipment(char *idRoom);
int isTimeSlotAvailable(char *time_slot, char *date, char *idRoom);
int isRestDayAvailable( Date date, int time_slot_int, char *idRoom );
Booking *prepareBooking( Search *search, RoomGtkBox room, char *idRoom );
Booking *prepareBookingPlanning(Calendar c);
int getPriceDrinks(int drinks[2], int idPlace);
void getIdRoom(GtkWidget *widget, Session *session);
void getCalendarWidgets(Calendar *c, GtkBuilder *builder);
int *moveInCalendar(int year, int month, int day, int move);
void getPlanningDrinksCheckbox(GtkWidget *widget, gpointer data);
unsigned int getPriceRoom(int idRoom);
MysqlSelect findReservationsInDB();
uint8_t hasRequiredEquipments(int requiredEquipments[4], char *idRoom);
int *getReservationDrinks(char *idBooking);
char *getPathMapPlace(uint32_t id_place);
uint8_t fileExists(char *path);

// SET DATA
void fillComboBoxRooms(GtkComboBoxText *place,gpointer room);
RoomGtkBox newRoomAvailable( MYSQL_ROW row);
void displayDataRoom(RoomGtkBox room, MYSQL_ROW row, Session *session);
ReservationBox newReservation();
delReservation *addDelReservation(Session *session, uint32_t id);
void displayReservationData(ReservationBox reservation,MYSQL_ROW row);
void displayRoomEquipments(GtkImage *equipments[4], char *idRoom);
void displayReservationDrinks(GtkImage *drinks[2], char *idBooking);
void displayTimeSlotComboBox(RoomGtkBox room, char *idRoom, Search *search);
void displayTimeSlotLabel(GtkLabel *label, char *idRoom, Date date, int time_slot);
void reserveRoomBySearch(GtkWidget *widget, Booking *b);
void insertDrinks(int drinks[2], MYSQL *conn);
void planningNumbers(Calendar *calendar, struct tm *date);
void click_button_planning(Session *session, char *idButton);
void updatePlanningNumbers(int *startDate, GtkLabel *days[5]);
void planningChangeWeek(GtkWidget *widget, gpointer data);
void updateWeekLabel( int *startDate, GtkLabel *week);
void setRoomInfo(Calendar *calendar);
void updateButtonsPlanning( Calendar *calendar, struct tm *td);
void showOrHidePlanningButton(int isAvailable, GtkWidget *button);
void chooseTimeSlot(GtkWidget *widget, Calendar *calendar);
void updateTimeSlotLabels(Calendar *c);
void reserveRoomByPlanning(Booking *b);
void updateTimeSlotComboPlanning(Calendar *calendar);
void onTimeSlotPlanningChanged(GtkWidget *widget, gpointer data);
void setDateReservation(char *dateSQL, GtkLabel *label);
void deleteReservation(GtkWidget *widget, delReservation *delReservation);
void abordDeleteReservation(GtkWidget *widget, GtkWidget *window);
void confirmDeleteReservation(GtkWidget *widget, gpointer data);
uint8_t checkDataInputPlace(GtkComboBox *place);
void focusDateCalendar(GtkCalendar *calendar);
uint8_t checkDataCalendar(GtkCalendar *calendar);
void checkDataNewRes(GtkWidget *widget, gpointer data);
void checkDataPlaceRoom(GtkWidget *widget, gpointer data);
void displayMapPlace(GtkBuilder *builder, uint32_t id_place);


// PRINT
void printSearchParameter(Search *seach);

//STYLE
void stylePlanningRoom(Session *session);
void background_color_if_sensitive(GtkWidget *widget, char* color);




//
