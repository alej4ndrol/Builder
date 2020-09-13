#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

enum CAMERA {
	SINGLE,
	DOUBLE,
	TRIPLE,
	QUADRUPLE
};

enum PROCESSOR {
	SINGLE_CORE,
	DOUBLE_CORE,
	QUAD_CORE,
	OCTA_CORE
};

enum DISPLAY {
	IPS,
	RETINA,
	AMOLED
};

enum CONNECTOR {
	LIGHTNING,
	USB_TYPE_C,
	MICRO_USB
};

class Smartphone {
	CAMERA camera;
	PROCESSOR processor;
	DISPLAY display;
	unsigned int battery;
	CONNECTOR connector;



public:
	string to_string_camera(CAMERA camera) {
		switch (camera) {
		case CAMERA::SINGLE:
			return "SINGLE camera";
		case CAMERA::DOUBLE:
			return "DOUBLE camera";
		case CAMERA::TRIPLE:
			return "TRIPLE camera";
		case CAMERA::QUADRUPLE:
			return "QUADRUPLE camera";
		}
	}

	string to_string_processor(PROCESSOR processor) {
		switch (processor) {
		case PROCESSOR::SINGLE_CORE:
			return "SINGLE_CORE processor";
		case PROCESSOR::DOUBLE_CORE:
			return "DOUBLE_CORE processor";
		case PROCESSOR::QUAD_CORE:
			return "QUAD_CORE processor";
		case PROCESSOR::OCTA_CORE:
			return "OCTA_CORE processor";
		}
	}

	string to_string_display(DISPLAY display) {
		switch (display) {
		case DISPLAY::IPS:
			return "IPS display";
		case DISPLAY::RETINA:
			return "RETINA display";
		case DISPLAY::AMOLED:
			return "AMOLED display";
		}
	}

	string to_string_connector(CONNECTOR connector) {
		switch (connector) {
		case CONNECTOR::USB_TYPE_C:
			return "USB_TYPE_C connector";
		case CONNECTOR::MICRO_USB:
			return "MICRO_USB connector";
		case CONNECTOR::LIGHTNING:
			return "LIGHTNING connector";
		}
	}

	void get_full_specs() {
		cout << "Your phone specifications: " << endl
			<< to_string_camera(camera) << endl
			<< to_string_processor(processor) << endl
			<< to_string_display(display) << endl
			<< "Battery " << battery << "mAh" << endl
			<< to_string_connector(connector) << endl;
	}

	friend class Iphone_builder;
	friend class Low_cost_builder;
};

class Smartphone_builder {
protected:
	CAMERA camera;
	PROCESSOR processor;
	DISPLAY display;
	unsigned int battery;
	CONNECTOR connector;

public:
	void set_connector(CONNECTOR connector) {
		this->connector = connector;
	}

	void set_display(DISPLAY display) {
		this->display = display;
	}

	void set_battery(unsigned int battery) {
		this->battery = battery;
	}

	virtual Smartphone* build() = 0;
};

class Iphone_builder : public Smartphone_builder {
public:
	virtual Smartphone* build() {
		Smartphone* smartphone = new Smartphone();
		smartphone->camera = QUADRUPLE;
		smartphone->processor = OCTA_CORE;
		smartphone->display = RETINA;
		smartphone->battery = battery;
		smartphone->connector = LIGHTNING;

		return smartphone;
	}
};

class Low_cost_builder : public Smartphone_builder {
public:
	virtual Smartphone* build() {
		Smartphone* smartphone = new Smartphone();
		smartphone->camera = SINGLE;
		smartphone->processor = SINGLE_CORE;
		smartphone->display = display;
		smartphone->battery = 3000;
		smartphone->connector = connector;

		return smartphone;
	}
};

void set_smartphone(unsigned int battery, CONNECTOR connector, DISPLAY display, Smartphone_builder& smartphone_builder) {

	smartphone_builder.set_battery(battery);
	switch (connector) {
	case CONNECTOR::USB_TYPE_C:
		smartphone_builder.set_connector(CONNECTOR::USB_TYPE_C);
		break;
	case CONNECTOR::MICRO_USB:
		smartphone_builder.set_connector(CONNECTOR::MICRO_USB);
		break;
	default:
		smartphone_builder.set_connector(CONNECTOR::MICRO_USB);
	}
	switch (display) {
	case DISPLAY::IPS:
		smartphone_builder.set_display(DISPLAY::IPS);
		break;
	case DISPLAY::AMOLED:
		smartphone_builder.set_display(DISPLAY::AMOLED);
		break;
	default:
		smartphone_builder.set_display(DISPLAY::IPS);
	}


	Smartphone* smartphone = smartphone_builder.build();
	smartphone->get_full_specs();
}

int main() {
	Iphone_builder builder1;
	Low_cost_builder builder2;
	unsigned int battery;
	CONNECTOR connector;
	DISPLAY display;
	int choise;
	cout << "Which connector do you want? (1 - USB_TYPE_C; 2- MICRO_USB) " << endl;
	cin >> choise;
	switch (choise)
	{
	case 1:
		connector = USB_TYPE_C;
		break;
	case 2:
		connector = MICRO_USB;
		break;
	default:
		connector = MICRO_USB;
		break;
	}
	cout << "Which display do you want? (1 - IPS; 2- AMOLED) " << endl;
	cin >> choise;
	switch (choise)
	{
	case 1:
		display = IPS;
		break;
	case 2:
		display = AMOLED;
		break;
	default:
		display = IPS;
		break;
	}
	cout << "Enter battery volume:  " << endl;
	cin >> battery;

	set_smartphone(battery, connector, display, builder1);
	set_smartphone(battery, connector, display, builder2);
}