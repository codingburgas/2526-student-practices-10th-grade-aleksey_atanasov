#include "App.h"

#include "LoginScreen.h"
#include "RegisterScreen.h"

App::App()
	: cinemaService(&data),
	authService(&userRepository)
{
	cinemaService.seedCinemas();

	currentScreen = Screen::MainMenu;

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
			currentScreen = Screen::MainMenu;
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
	InitWindow(900, 600, "MovieFlow");

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
		}

		EndDrawing();
	}

	CloseWindow();
}
