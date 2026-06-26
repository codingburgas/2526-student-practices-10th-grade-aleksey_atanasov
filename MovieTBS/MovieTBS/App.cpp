#include "App.h"

#include "LoginScreen.h"
#include "RegisterScreen.h"
#include "MoviesScreen.h"

#include <ctime>
#include <iomanip>
#include <sstream>

App::App()
	: cinemaService(&data),
	authService(&userRepository)
{
	cinemaService.seedCinemas();

	currentScreen = Screen::Login;

	usernameInput = "";
	passwordInput = "";

	usernameActive = false;
	passwordActive = false;

	statusMessage = "";

	isLoggedIn = false;
	currentUser = "";

	usernameBox = { 0, 0, 0, 0 };
	passwordBox = { 0, 0, 0, 0 };

	loginButton = { 0, 0, 0, 0 };
	registerButton = { 0, 0, 0, 0 };
	createAccountButton = { 0, 0, 0, 0 };

	selectedMovieIndex = -1;

	// Initialize movies screen with movies from repository
	moviesScreen.setMovies(movieRepository.getMovies());

	// Initialize seat selection with global occupancy map
	seatSelectionScreen.setSeatOccupancy(globalSeatOccupancy);
}

void App::handleLoginScreen()
{
	loginScreen.update();

	// Check if login button is pressed
	if (loginScreen.isLoginButtonPressed())
	{
		std::string username = loginScreen.getUsername();
		std::string password = loginScreen.getPassword();

		// Validate inputs
		if (username.empty() || password.empty())
		{
			loginScreen.setStatusMessage("Username and password cannot be empty!");
			return;
		}

		// Try to log in
		if (authService.login(username, password))
		{
			loginScreen.setStatusMessage("Login successful!");
			isLoggedIn = true;
			currentUser = username;
			loginScreen.clearInputs();
			currentScreen = Screen::Movies;
		}
		else
		{
			// Check if user exists
			if (authService.usernameExists(username))
			{
				loginScreen.setStatusMessage("Incorrect password!");
			}
			else
			{
				loginScreen.setStatusMessage("User not found!");
			}
		}
	}

	// Check if register button is pressed
	if (loginScreen.isRegisterButtonPressed())
	{
		loginScreen.clearInputs();
		loginScreen.resetButtonStates();
		registerScreen.clearInputs();
		registerScreen.resetButtonStates();
		currentScreen = Screen::Register;
	}

	// Check if back button is pressed
	if (loginScreen.isBackButtonPressed())
	{
		loginScreen.clearInputs();
		loginScreen.resetButtonStates();
		currentScreen = Screen::MainMenu;
	}
}

void App::handleRegisterScreen()
{
	registerScreen.update();

	// Check if create account button is pressed
	if (registerScreen.isCreateAccountButtonPressed())
	{
		std::string username = registerScreen.getUsername();
		std::string password = registerScreen.getPassword();

		// Validate inputs
		if (username.empty() || password.empty())
		{
			registerScreen.setStatusMessage("Username and password cannot be empty!");
			return;
		}

		// Try to register
		if (authService.registerUser(username, password))
		{
			registerScreen.setStatusMessage("Account created successfully!");
			registerScreen.clearInputs();

			// Return to login screen immediately
			registerScreen.resetButtonStates();
			currentScreen = Screen::Login;
		}
		else
		{
			registerScreen.setStatusMessage("User already exists!");
		}
	}

	// Check if back button is pressed
	if (registerScreen.isBackButtonPressed())
	{
		registerScreen.clearInputs();
		registerScreen.resetButtonStates();
		currentScreen = Screen::Login;
	}
}

void App::handleMoviesScreen()
{
	moviesScreen.update();

	// Check if logout button is pressed
	if (moviesScreen.isLogoutButtonPressed())
	{
		isLoggedIn = false;
		currentUser = "";
		currentScreen = Screen::MainMenu;
		selectedMovieIndex = -1;
	}

	// Check if view details is pressed
	int hoveredMovie = moviesScreen.getHoveredMovieIndex();
	if (hoveredMovie >= 0 && moviesScreen.isViewDetailsPressed(hoveredMovie))
	{
		selectedMovieIndex = hoveredMovie;
		movieDetailsScreen.setMovie(&movieRepository.getMovies()[selectedMovieIndex]);
		currentScreen = Screen::MovieDetails;
	}

	// Check if My Tickets button is pressed (only when logged in)
	if (!currentUser.empty() && moviesScreen.isMyTicketsPressed())
	{
		// Prepare tickets for current user and navigate
		myTicketsScreen.setBookings(bookingRepository.getBookingsForUser(currentUser));
		currentScreen = Screen::MyTickets;
	}

}

void App::handleMovieDetailsScreen()
{
	movieDetailsScreen.update();

	// Check if back button is pressed
	if (movieDetailsScreen.isBackButtonPressed())
	{
		currentScreen = Screen::Movies;
		selectedMovieIndex = -1;
	}

	// Check if choose seats button is pressed
	if (movieDetailsScreen.isChooseSeatsButtonPressed())
	{
		// Navigate to seat selection screen
		const Movie* selectedMovie = &movieRepository.getMovies()[selectedMovieIndex];
		seatSelectionScreen.setMovie(selectedMovie);
		seatSelectionScreen.setSeatOccupancy(globalSeatOccupancy);
		currentScreen = Screen::SeatSelection;
	}
}

void App::handleSeatSelectionScreen()
{
	seatSelectionScreen.update();

	// Check if back button is pressed
	if (seatSelectionScreen.isBackButtonPressed())
	{
		currentScreen = Screen::MovieDetails;
	}

	// Check if book tickets button is pressed
	if (seatSelectionScreen.isBookTicketsButtonPressed())
	{
		// Get booking information
		std::vector<std::string> selectedSeats = seatSelectionScreen.getSelectedSeats();
		double totalPrice = seatSelectionScreen.getTotalPrice();
		const Movie* selectedMovie = seatSelectionScreen.getSelectedMovie();

		// Mark seats as occupied in global map
		seatSelectionScreen.markSeatsAsOccupied(selectedSeats);
		globalSeatOccupancy = seatSelectionScreen.getSeatOccupancy();

		// Create booking record and store in repository
		// Format current date/time
		time_t now = time(nullptr);
		struct tm localTime;
	#ifdef _WIN32
		localtime_s(&localTime, &now);
	#else
		localtime_r(&now, &localTime);
	#endif
		char dateBuf[64];
		strftime(dateBuf, sizeof(dateBuf), "%Y-%m-%d %H:%M:%S", &localTime);
		std::string dateStr(dateBuf);

		Booking newBooking(0, currentUser, selectedMovie->getTitle(), selectedSeats, dateStr, totalPrice);
		int assignedId = bookingRepository.addBooking(newBooking);

		// Prepare confirmation screen
		bookingConfirmationScreen.setBookingInfo(selectedMovie, selectedSeats, totalPrice);
		currentScreen = Screen::BookingConfirmation;

		// Set transient status message
		statusMessage = "Booking confirmed!";
		statusTimer = 3.0f; // show for 3 seconds
	}
}

void App::handleBookingConfirmationScreen()
{
	bookingConfirmationScreen.update();

	// Check if back to movies button is pressed
	if (bookingConfirmationScreen.isBackToMoviesButtonPressed())
	{
		currentScreen = Screen::Movies;
		selectedMovieIndex = -1;
	}
}

void App::handleMyTicketsScreen()
{
	myTicketsScreen.update();

	// Back to Movies
	if (myTicketsScreen.isBackButtonPressed())
	{
		currentScreen = Screen::Movies;
		selectedMovieIndex = -1;
	}

	// Handle pending cancellation confirmation
	int pending = myTicketsScreen.getPendingCancelBookingIndex();
	if (pending >= 0)
	{
		if (myTicketsScreen.isConfirmYesPressed())
		{
			int bookingId = myTicketsScreen.getBookingIdAt(pending);
			Booking removed;
			if (bookingRepository.removeBookingById(bookingId, removed))
			{
				// Free seats in global occupancy
				auto seats = removed.getSeats();
				for (const auto& s : seats)
				{
					globalSeatOccupancy[s] = false;
				}

				// Update seat selection occupancy
				seatSelectionScreen.setSeatOccupancy(globalSeatOccupancy);

				// Refresh tickets list for current user
				myTicketsScreen.setBookings(bookingRepository.getBookingsForUser(currentUser));
			}

			myTicketsScreen.clearPendingCancel();
		}
		else if (myTicketsScreen.isConfirmNoPressed())
		{
			myTicketsScreen.clearPendingCancel();
		}
	}
}


void App::handleMainMenu()
{
	Vector2 mousePosition = GetMousePosition();

	Rectangle loginButton =
	{
		(float)(GetScreenWidth() - 150),
		20,
		140,
		40
	};

	// Main Menu -> Login
	if (CheckCollisionPointRec(mousePosition, loginButton) &&
		IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		loginScreen.clearInputs();
		loginScreen.resetButtonStates();
		currentScreen = Screen::Login;
	}
}

void App::run()
{
	InitWindow(900, 600, "MovieTBS");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		int width = GetScreenWidth();
		int height = GetScreenHeight();

		Vector2 mousePosition = GetMousePosition();

		// Handle screen transitions
		if (currentScreen == Screen::MainMenu)
		{
			handleMainMenu();
		}
		else if (currentScreen == Screen::Login)
		{
			handleLoginScreen();
		}
		else if (currentScreen == Screen::Register)
		{
			handleRegisterScreen();
		}
		else if (currentScreen == Screen::Movies)
		{
			handleMoviesScreen();
		}
		else if (currentScreen == Screen::MovieDetails)
		{
			handleMovieDetailsScreen();
		}
		else if (currentScreen == Screen::SeatSelection)
		{
			handleSeatSelectionScreen();
		}
		else if (currentScreen == Screen::BookingConfirmation)
		{
			handleBookingConfirmationScreen();
		}
		else if (currentScreen == Screen::MyTickets)
		{
			handleMyTicketsScreen();
		}

		BeginDrawing();

		ClearBackground(BEIGE);

		// LOGIN button rectangle - used in MainMenu
		Rectangle loginButton =
		{
			(float)(width - 150),
			20,
			140,
			40
		};

		switch (currentScreen)
		{
		case Screen::MainMenu:

			DrawText(
				"MovieFlow",
				width / 2 - 100,
				60,
				40,
				BLACK
			);

			DrawText(
				"Welcome to MovieFlow",
				width / 2 - 120,
				150,
				25,
				DARKGRAY
			);

			DrawText(
				"Browse movies and book tickets",
				width / 2 - 170,
				190,
				20,
				GRAY
			);

			// LOGIN button text - Top right
			Vector2 mousePos = GetMousePosition();

			Color loginTextColor = DARKBLUE;
			if (CheckCollisionPointRec(mousePos, loginButton))
			{
				loginTextColor = BLUE;
			}

			DrawText(
				"LOGIN",
				width - 140,
				28,
				24,
				loginTextColor
			);


			if (isLoggedIn)
			{
				std::string userInfo = "Logged in as: " + currentUser;
				DrawText(
					userInfo.c_str(),
					width / 2 - MeasureText(userInfo.c_str(), 18) / 2,
					300,
					18,
					DARKGREEN
				);
			}

			break;

		case Screen::Login:

			loginScreen.draw(
				width,
				height
			);

			break;

		case Screen::Register:

			registerScreen.draw(
				width,
				height
			);

			break;

		case Screen::Movies:

			moviesScreen.draw(
				width,
				height,
				currentUser
			);

			break;

		case Screen::MovieDetails:

			movieDetailsScreen.draw(
				width,
				height,
				currentUser
			);

			break;

		case Screen::SeatSelection:

			seatSelectionScreen.draw(
				width,
				height,
				currentUser
			);

			break;

		case Screen::MyTickets:

			myTicketsScreen.draw(
				width,
				height,
				currentUser
			);

			break;

		case Screen::BookingConfirmation:

			bookingConfirmationScreen.draw(
				width,
				height,
				currentUser
			);

			break;
		}

		// Draw transient status message if any
		if (statusTimer > 0.0f && !statusMessage.empty())
		{
			int msgW = MeasureText(statusMessage.c_str(), 18);
			DrawRectangle((width - msgW - 40) / 2, 10, msgW + 40, 36, LIGHTGRAY);
			DrawText(statusMessage.c_str(), (width - msgW) / 2, 16, 18, BLACK);
			statusTimer -= GetFrameTime();
		}

		EndDrawing();
	}

	CloseWindow();
}
