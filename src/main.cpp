#include "swangui.h"

int main() 
{
	InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "SwanGUI Demo");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetExitKey(KEY_NULL);
	MaximizeWindow();
	SetTargetFPS(144);

	Font custom_font= LoadFontEx("source-sans-pro.bold.ttf", 14, 0, 0);

	Vector2 panelPos=  {0, 0};
	Vector2 panelSize= {150, 1080};

	SwanGui swanGui;

	auto panel= std::make_shared<Panel>(panelPos, panelSize, custom_font);
	
	auto button1= std::make_shared<Button>("Do Something", [](){std::cout<< "did something"<< std::endl;});
	auto button2= std::make_shared<Button>("CHANGE RES", [](){std::cout<< "changed resolution"<< std::endl;}, false);
	auto button3= std::make_shared<Button>("RENDER", [](){std::cout<< "rendered"<< std::endl;}, true);
	
	auto comment1= std::make_shared<Comment>("this is a comment");
	auto comment2= std::make_shared<Comment>("and another comment");

	bool is_this_enabled= false;
	auto checkbox1= std::make_shared<CheckBox>("Bloom", is_this_enabled);
	auto checkbox2= std::make_shared<CheckBox>("Stars", is_this_enabled);

	int speed= 50;
	auto slider1= std::make_shared<Slider>("Speed", speed, 1, 0, 100);
	auto slider2= std::make_shared<Slider>("Speed", speed, 1, 0, 100);

	Texture2D test_texture1= LoadTexture("test.png");
	Texture2D test_texture2= LoadTexture("fish.png");
	auto thumbnail1= std::make_shared<Thumbnail>("test.png", test_texture1, [](){}, "Select");
	auto thumbnail2= std::make_shared<Thumbnail>("fish.png", test_texture2, [](){}, "Rename");

	auto billboard1= std::make_shared<Billboard>(test_texture2);

	int frame_delay = 7;
	auto billboard2 = std::make_shared<BillboardGif>("swan.gif", frame_delay);

	auto slider3= std::make_shared<Slider>("frame delay", frame_delay, 1, 0, 50);

	auto thumbnailGif = std::make_shared<ThumbnailGif>("Animated GIF", "swan.gif", [](){std::cout << "GIF Thumbnail clicked" << std::endl;}, "Select",7);

	auto drawSceneFunction = [](Camera3D& camera) {
		DrawPlane((Vector3){ 0, 0, 0 }, (Vector2){ 20, 20 }, DARKGREEN);
		DrawCube((Vector3){0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, WHITE);
		DrawCube(camera.position, 1, 1, 1, RED);
	};

	Camera3D camera= {0};
	camera.position= (Vector3){0.0f, 2.0f, -10.0f};
	camera.target= (Vector3){0.0f, 0.0f, 0.0f};
	camera.up= (Vector3){0.0f, 1.0f, 0.0f};
	camera.fovy= 65.0f;

	auto cameraView = std::make_shared<CameraView3D>(camera, 150, drawSceneFunction);

	panel->addElement(button1);
	panel->addElement(button2);

	panel->addElement(checkbox1);
	panel->addElement(checkbox2);

	panel->addElement(slider1);
	panel->addElement(slider2);

	panel->addElement(button3);	

	panel->addElement(comment1);
	panel->addElement(comment2);

	panel->addElement(thumbnail1);
	panel->addElement(thumbnail2);

	panel->addElement(billboard1);
	panel->addElement(billboard2);

	panel->addElement(slider3);

	panel->addElement(cameraView);

	panel->addElement(thumbnailGif);

	swanGui.AddPanel(panel);

	while (!WindowShouldClose())
	{
		swanGui.Update();

		BeginDrawing();
			ClearBackground( (Color){20, 20, 20, 255} );
			swanGui.Draw();

		EndDrawing();
	}
	CloseWindow();
	return 0;
}