#pragma once
#include <stdint.h>
#include "IInput.h"

class GameInput : public Input
{
public:
	GameInput() = delete;
	~GameInput() = default;
	void update();
protected:
	virtual bool IsKeyPressedImpl(int keycode) override;
private:
	uint8_t* keyboard;
};