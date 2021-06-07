namespace 화면그리기 {

// Main main;

class Main {
	Main() {
		regtrg(이벤트2_화면그리기, 트리거_필수이벤트, TriggerCallbackType2(draw));
	}

	bool draw(trgevent2 e) {
		Painter p;

		p.drawText("테스트.", 200, 200, -1, 1, 0xffff0000);
		p.drawText("색상\x1b[1x테스트.", 200, 250, -1, 1);

		p.drawRect(Rectangle(Point(200, 300), Size(100, 100)), 0xffff0000);
		p.drawText("drawRect", Point(200, 300));

		p.drawFilledRect(Rectangle(Point(200, 450), Size(100, 100)), 0xffff0000);
		p.drawText("drawFilledRect", Point(200, 450));

		p.drawFace(FACE_SMALL, 0, Rectangle(Point(400, 200), Size(32, 40)));
		p.drawFace(FACE_SMALL, 0, Rectangle(Point(400, 250), Size(32, 40)), FACE_R);
		p.drawText("32x40", Point(400, 180));

		p.drawFace(FACE_SMALL, 0, Rectangle(Point(460, 200), Size(64, 80)));
		p.drawFace(FACE_SMALL, 0, Rectangle(Point(460, 300), Size(64, 80)), FACE_R);
		p.drawText("64x80", Point(460, 180));

		p.drawFace(FACE_BIG, 0, Rectangle(Point(550, 200), Size(240, 240)));
		p.drawText("240x240", Point(550, 180));
		return false;
	}
};

} // namespace