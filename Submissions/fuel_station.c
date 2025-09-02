#include <stdio.h>
//constants like prices or taxes, discounts
const double PRICE_REGULAR = 3.00;
const double PRICE_PREMIUM = 4.00;
const double PRICE_DIESEL  = 3.50;


//limit per transaction
const double LIMIT_GAS_GAL    = 200.0; 
const double LIMIT_DIESEL_GAL = 400.0;


//tax per vehicle type
const double TAX_MOTORCYCLE = 0.02;
const double TAX_CAR        = 0.03;
const double TAX_TRUCK      = 0.01;


//bulk buy discounts
const double DISC_BULK_30 = 0.05; 
const double DISC_BULK_50 = 0.10; 
const double DISC_LOYAL   = 0.02;


// max stock per fuel type
double stock_regular = 1000.0;
double stock_premium = 1000.0;
double stock_diesel  = 1000.0;

int    total_customers = 0;
double total_gallons   = 0.0;
double sales_revenue   = 0.0; 
double tax_collected   = 0.0;
double discounts_given = 0.0;
double customer_payments = 0.0;
int    rcpt_number = 1;

//increments per costumer served
int next_customer_id = 1; 

int motorcycles = 0, cars = 0, trucks = 0;

int main(void){
    int choice;
    int exit_confirm;
    
    


    while(1){

        //print the main page showing prices and options
        printf("=========================================================\n");
        printf("   WELCOME TO TurboFill FUEL STATION MANAGEMENT SYSTEM\n");
        printf("=========================================================\n\n");

        printf("========= CURRENT PRICING & POLICIES =========\n");
        printf("Fuel Rates:\n");
        printf("  Regular Gas : $%.2f/gal (Max: %.0f gal/transaction)\n", PRICE_REGULAR, LIMIT_GAS_GAL);
        printf("  Premium Gas : $%.2f/gal (Max: %.0f gal/transaction)\n", PRICE_PREMIUM, LIMIT_GAS_GAL);
        printf("  Diesel      : $%.2f/gal (Max: %.0f gal/transaction)\n\n",PRICE_DIESEL, LIMIT_DIESEL_GAL);

        printf("State Fuel Tax Rates:\n");
        printf("  Motorcycle  : %.0f%%\n", TAX_MOTORCYCLE * 100.0);
        printf("  Car         : %.0f%%\n", TAX_CAR * 100.0);
        printf("  Truck       : %.0f%%\n\n", TAX_TRUCK * 100.0);

        printf("Bulk Discount Rates:\n");
        printf("  30+ gallons : %.0f%% off total\n",  DISC_BULK_30 * 100.0);
        printf("  50+ gallons : %.0f%% off total\n\n", DISC_BULK_50 * 100.0);

        printf("Loyalty Program: Additional %.0f%% off total\n", DISC_LOYAL * 100.0);
        printf("=============================================\n\n");

        //main manu goto option, checks input from range 1-3
        MainMenu:
        printf("\n========= SYSTEM MODE SELECTION =========\n");
        printf("1. Daily Operations (Customer Service)\n");
        printf("2. Station Management (Administrative)\n");
        printf("3. Exit System\n");
        printf("=========================================\n");
        printf("Select Mode:");

        //get user input
        scanf("%d", &choice);

        //logic to check if input is in correct range
        if( choice > 3 || choice < 1){ 
            printf("Invalid mode selection! Please choose 1-3.\n\n");
            goto MainMenu;
            }   
        
        //switch statement to go to any of the 3 possible menues
        switch(choice){
            case 1:{
                int DailyChoice;

                DailyOptions:
                printf("\n");
                printf("========= DAILY OPERATIONS MODE =========\n");
                printf("1. Serve New Customer\n");
                printf("2. View Current Day Summary\n");
                printf("3. Return to Main Menu\n");
                printf("========================================\n");
                printf("Choice: ");
                scanf("%d", &DailyChoice);

                //if the choice is in the correct range go to next menu
                if(DailyChoice > 3 || DailyChoice < 1){
                    printf("invalid choice! Please Select 1-3\n");
                    goto DailyOptions;
                } else if(DailyChoice == 3){
                    goto MainMenu;
                }

                //Daily operations mode switch
                switch(DailyChoice){

                    //new receipt being created,
                    case 1:{
                        int fuelChoice;
                        double qty = 0.0;
                        double available = 0.0;
                        double trans_limit = 0.0;
                        const char* fuel_name = "";

                        printf("\n--- CUSTOMER #%d ---\n", next_customer_id);
                        if (stock_regular > 0.0)
                            printf("1. Regular Gas ($%.2f/gal) - Stock: %.1f gal\n", PRICE_REGULAR, stock_regular);
                        else
                            printf("1. Regular Gas ($%.2f/gal) - OUT OF STOCK\n", PRICE_REGULAR);

                        if (stock_premium > 0.0)
                            printf("2. Premium Gas ($%.2f/gal) - Stock: %.1f gal\n", PRICE_PREMIUM, stock_premium);
                        else
                            printf("2. Premium Gas ($%.2f/gal) - OUT OF STOCK\n", PRICE_PREMIUM);

                        if (stock_diesel > 0.0)
                            printf("3. Diesel ($%.2f/gal)      - Stock: %.1f gal\n", PRICE_DIESEL, stock_diesel);
                        else
                            printf("3. Diesel ($%.2f/gal)      - OUT OF STOCK\n", PRICE_DIESEL);

                        printf("Fuel Choice:");
                        scanf("%d",&fuelChoice);
                        

                        //check correct choice range
                        if(fuelChoice > 3 || fuelChoice < 1){
                            while(fuelChoice > 3 || fuelChoice < 1){
                                printf("invalid choice! Select Fuel(1-3): \n");
                                scanf("%d", &fuelChoice);
                            }
                        }

                        //gas type selector
                         if (fuelChoice == 1) {
                            available = stock_regular;
                            trans_limit = LIMIT_GAS_GAL;
                            fuel_name = "Regular Gas";
                        } else if (fuelChoice == 2) {
                            available = stock_premium;
                            trans_limit = LIMIT_GAS_GAL;
                            fuel_name = "Premium Gas";
                        } else { 
                            available = stock_diesel;
                            trans_limit = LIMIT_DIESEL_GAL;
                            fuel_name = "Diesel";
                        }

                        if(available <= 0.0){
                            printf("Sorry, selected fuel is OUT OF STOCK! Please choose a different fuel.");
                            goto DailyOptions;
                        }

                        //block to check if quantity can be used for transaction
                        {
                            int qty_ok = 0;
                            printf("Enter quantity in gallons (Max: %.0f): ", trans_limit);
                            while (!qty_ok) {
                                scanf("%lf", &qty);

                                //take user to daily options in case needed fuel is not in stock
                                if (qty > available){
                                    printf("Insufficient %s stock! Available %0.1f\n", fuel_name, available);
                                    printf("transaction cancelled due to insufficient stock.\n");
                                    goto DailyOptions;
                                } else if (qty <= 0.0 || qty > trans_limit) {
                                    printf("Invalid quantity! Enter a proper amount (max %.0f gal): ", trans_limit);
                                    continue;
                                }
                                qty_ok = 1;
                            }
                        }
                        int vehicleChoice;
                        const char* vehicle_name ="";

                        printf("\n\nSelect Vehicle Type:\n");
                        printf("1. Motorcycle (2%% state fuel tax)\n");
                        printf("2. Car (3%% state fuel tax)\n");
                        printf("3. Truck (1%% state fuel tax)\n");
                        printf("Vehicle Choice:");
                        scanf("%d", &vehicleChoice);

                        //invalid choice prompt
                        if(vehicleChoice < 1 || vehicleChoice> 3){
                            while(vehicleChoice < 1 || vehicleChoice> 3){
                                printf("Invalid Choice! Select Vehicle (1-3):  \n");
                                scanf("%d", &vehicleChoice);
                            }
                        }

                        //stop user from putting diesel on motorcycle
                        if(vehicleChoice ==1 && fuelChoice == 3){
                            printf("Invalid combination! Motorcycles cannot use diesel fuel.\n");
                            printf("Please go back and select gasoline (Regular or Premium).\n");
                            goto DailyOptions;
                        }

                        //make sure user is making a good decision
                        if(vehicleChoice == 2 && fuelChoice == 3){
                            int confirm = 0;
                            printf("Note: Most cars use gasoline. Are you sure this car uses diesel? (1=Yes, 0=No):");
                            scanf("%d", &confirm);
                            if(confirm == 0){
                                goto DailyOptions;
                            } else if (confirm < 0 || confirm > 1 ){
                                while(confirm < 0 || confirm > 1){
                                    printf("Invalid input! Enter 1 for Yes, 0 for No:");
                                    scanf("%d", &confirm);
                                    if(confirm == 0){
                                        goto DailyOptions;
                                    }
                                }
                            }
                        }

                        if (vehicleChoice == 1){
                            vehicle_name = "Motorcycle";
                        } else if(vehicleChoice == 2){
                            vehicle_name = "Car";
                        } else {
                            vehicle_name = "Truck";
                        }

                        int Loyalty = 0;
                        printf("Is the customer a loyalty member? (1=Yes, 0=NO):");
                        scanf("%d", &Loyalty);
                        if(Loyalty < 0 || Loyalty > 1){
                            while(Loyalty < 0 || Loyalty > 1){
                                printf("Invalid input! Enter 1 for Yes, 0 for No:");
                                scanf("%d", &Loyalty);
                            }
                            
                        }

                        //math calculations for printing the receipt
                        double galon_rate = 0.0;

                        //calculate the rate based on past selection
                        if(fuelChoice == 1){ galon_rate = PRICE_REGULAR;}
                        else if (fuelChoice == 2){galon_rate = PRICE_PREMIUM;}
                        else {galon_rate = PRICE_DIESEL;}

                        //get the current cost at this point with no discounts
                        double base_cost = qty * galon_rate;

                        //calculate the tax base on the vehicle
                        double tax_rate = 0.0;
                        if(vehicleChoice == 1){tax_rate = TAX_MOTORCYCLE;}
                        else if(vehicleChoice == 2){tax_rate = TAX_CAR;}
                        else {tax_rate = TAX_TRUCK;}

                        double state_tax = base_cost * tax_rate;

                        //get total of the discounts
                        double subtotal_for_discounts = base_cost + state_tax;
                        double bulk_disc = 0.0;
                        if (qty >= 50.0) {
                            bulk_disc = subtotal_for_discounts * DISC_BULK_50;   
                        } else if (qty >= 30.0) {
                            bulk_disc = subtotal_for_discounts * DISC_BULK_30;  
                        }

                
                        double total_after_bulk = subtotal_for_discounts - bulk_disc;
                        double loyal_disc = (Loyalty == 1) ? ((base_cost + state_tax)*DISC_LOYAL) : 0.0;

                        //final ammount
                        double total_payable = total_after_bulk - loyal_disc;

                        //Receipt format
                        printf("==========================================\n");
                        printf("            FUEL RECEIPT #%03d\n", rcpt_number);
                        printf("==========================================\n");
                        printf(" Fuel Type    : %s\n", fuel_name);
                        printf(" Vehicle Type : %s\n", vehicle_name);
                        printf(" Quantity     : %.2f   gal\n", qty);
                        printf(" Rate         : $%.2f  /gal\n", galon_rate);
                        printf(" Loyalty      : %s\n", (Loyalty == 1) ? "Yes" : "No");
                        printf("==========================================\n");
                        printf(" Base Cost    : $%.2f\n", base_cost);
                        printf(" State Tax    : $%.2f\n", state_tax);
                        if (bulk_disc > 0.0) {
                            printf(" Bulk Discount: -$%.2f\n", bulk_disc);
                        }
                        if (loyal_disc > 0.0) {
                            printf(" Loyalty Disc.: -$%.2f\n", loyal_disc);
                        }
                        printf("==========================================\n");
                        printf(" TOTAL PAYABLE: $%.2f\n", total_payable);
                        printf("==========================================\n");

                        //update data for next cosutmer and possible stock alers
                        if (fuelChoice == 1)      stock_regular -= qty;
                        else if (fuelChoice == 2) stock_premium -= qty;
                        else                      stock_diesel  -= qty;

                        if(stock_regular < 200 || stock_diesel < 200 || stock_premium < 200){
                            if (stock_regular == 0.0 || stock_diesel == 0.0 || stock_premium == 0.0){
                                printf("*** CRITICAL ALERT: Emergency fuel stock level! ***\n");
                            } else{
                                printf("*** LOW STOCK WARNING ***\n");
                            }
                            if(stock_regular < 200){
                                
                                printf("Regular Gas: %.1f gal remaining\n", stock_regular);
                            }
                            if(stock_diesel < 200){
                                printf("Diesel: %.1f gal remaining \n", stock_diesel);
                            }
                            if(stock_premium < 200){
                                printf("Premium gas: %.1f gal remaining\n", stock_premium);
                            }
                        }

                        //update all finacial counters
                        rcpt_number++;
                        total_customers++;
                        total_gallons     += qty;
                        sales_revenue     += base_cost;             
                        tax_collected     += state_tax;              
                        discounts_given   += (bulk_disc + loyal_disc);
                        customer_payments += total_payable;

                        //increase data of vehicle type
                        if (vehicleChoice == 1)      motorcycles++;
                        else if (vehicleChoice == 2) cars++;
                        else                         trucks++;
                        printf("\n");
                        printf("Transaction completed successfully!\n");

                        next_customer_id++;
                        goto DailyOptions;
                    }
                    case 2:

                        //forat for the current day summary section
                        printf("==========================================\n");
                        printf("             CURRENT DAY SUMMARY\n");
                        printf("==========================================\n");
                        printf(" Total Customers    : %d\n", total_customers);
                        printf(" Total Fuel Sold    : %.1f   gal\n", total_gallons);
                        printf(" Sales Revenue      : $%.2f\n", sales_revenue);
                        printf(" State Tax Collected: $%.2f\n", tax_collected);
                        printf(" Total Discounts    : $%.2f\n", discounts_given);
                        printf(" Customer Payments  : $%.2f\n", customer_payments);

                        ///net income comes from customer payments - state tax collected
                        printf(" Station Net Income : $%.2f\n", (customer_payments - tax_collected));
                        printf("==========================================\n");

                        printf(" Vehicle Distribution:\n");
                        printf(" Motorcycles        : %d\n", motorcycles);
                        printf(" Cars               : %d\n", cars);
                        printf(" Trucks             : %d\n", trucks);
                        printf("==========================================\n");

                        //take the averages and meke sure no 0 division
                        if (total_customers > 0) {
                            double avg_payment = customer_payments / total_customers;
                            double avg_fuel    = total_gallons / total_customers;
                            printf(" Average Payment    : $%.2f\n", avg_payment);
                            printf(" Avg Fuel/Customer  : %.2f   gal\n", avg_fuel);
                        } else {
                            printf(" Average Payment    : $0.00\n");
                            printf(" Avg Fuel/Customer  : 0.00   gal\n");
                        }
                        printf("==========================================\n\n");
                        goto DailyOptions;
                    case 3:
                        goto MainMenu;
                        break;
                    default:
                        printf("Invalid mode selection! Please choose 1-3.\n\n");
                        goto DailyOptions;
                }
                
                break;
            }
            case 2:
                {
                int Choice;
                double base_stock = 1000.0;
                double sold_regular = base_stock - stock_regular;
                double sold_premium = base_stock - stock_premium;
                double sold_diesel  = base_stock - stock_diesel;

                //if stock is less than 50 the alert is critical, if less than 200 then low, if not the normal
                char *regular_status = (stock_regular < 50.0) ? "Critical" : (stock_regular < 200) ? "Low" : "Normal";
                char *premium_status = (stock_premium < 50.0) ? "Critical" : (stock_premium < 200) ? "Low" : "Normal";
                char *diesel_status = (stock_diesel < 50.0) ? "Critical" : (stock_diesel < 200) ? "Low" : "Normal";
                
                /* Stock status helper: CRITICAL <50, LOW <200, else NORMAL */
                ManagementOptions:    
                printf("\n========= STATION MANAGEMENT =========\n");
                printf("1. Fuel Inventory Status\n");
                printf("2. Return to Main Menu\n");
                printf("======================================\n");
                printf("Choice:");
                scanf("%d", &Choice);
                if(Choice < 1 ||Choice > 2){
                    printf("Invalid Choice! Please select 1-2.");
                    goto ManagementOptions;
                }
                if(Choice == 2){
                    goto MainMenu;
                }
                //inventory status 
                printf("==========================================\n");
                printf("             FUEL INVENTORY STATUS\n");
                printf("==========================================\n");
                printf(" Stock Status Thresholds:\n");
                printf("   CRITICAL: < 50 gallons\n");
                printf("   LOW: < 200 gallons\n");
                printf("   NORMAL: >= 200 gallons\n");
                printf("==========================================\n");

                printf(" REGULAR GAS:\n");
                printf("   Current Stock    : %.1f    gal\n", stock_regular);
                printf("   Sold Today       : %.1f    gal\n", sold_regular);
                printf("   Stock Status     : %s\n", regular_status);
                printf("==========================================\n");

                printf(" PREMIUM GAS:\n");
                printf("   Current Stock    : %.1f    gal\n", stock_premium);
                printf("   Sold Today       : %.1f    gal\n", sold_premium);
                printf("   Stock Status     : %s\n", premium_status);
                printf("==========================================\n");

                printf(" DIESEL:\n");
                printf("   Current Stock    : %.1f    gal\n", stock_diesel);
                printf("   Sold Today       : %.1f    gal\n", sold_diesel);
                printf("   Stock Status     : %s\n", diesel_status);
                printf("==========================================\n");
                goto ManagementOptions;
                }
            //exit case, double checks user reasoning to make sure they want to leave
            case 3:
                printf("\nAre you sure you want to exit? (1=Yes, 0=No): ");
                scanf("%d",&exit_confirm);

                //nice exit message 
                if(exit_confirm == 1){
                    ExitMessage:
                    printf("=========================================\n");
                    printf("Thank you for using TurboFill Fuel Station!\n");
                    printf("            System Exiting...               \n");
                    printf("=========================================\n");
                    return 0;


                //go back to main manu
                } else if(exit_confirm == 0){
                    printf("Exit cancelled. Returning to main menu.\n\n");
                    goto MainMenu;

                    //keep checking user input and re-promting for a correct option
                } else if(exit_confirm > 1 || exit_confirm< 0){
                    while(exit_confirm > 1 || exit_confirm< 0){
                        printf("Invalid input! Enter 1 for Yes, 0 for No:");
                        scanf("%d", &exit_confirm);
                    }
                    //got to original exit case and exit program
                    if(exit_confirm == 1){

                        goto ExitMessage;
                    // got to the main menu
                    } else if (exit_confirm == 0){
                        printf("Exit cancelled. Returning to main menu.\n\n");
                        goto MainMenu;
                    }
                }
                break;
            default:
                printf("Invalid mode selection! Please choose 1-3.\n\n");
                goto MainMenu;
        }
    }
}
