/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/wrap/slide_wrap.h"
#include "ui/chat/message_bar.h"

namespace Main {
class Session;
} // namespace Main

namespace Ui {
class IconButton;
class PlainShadow;
} // namespace Ui

namespace HistoryView {

enum class PinnedIdType;
struct PinnedBarId {
	FullMsgId message;
	PinnedIdType type = PinnedIdType();

	bool operator<(const PinnedBarId &other) const {
		return std::tie(message, type) < std::tie(other.message, other.type);
	}
	bool operator==(const PinnedBarId &other) const {
		return std::tie(message, type) == std::tie(other.message, other.type);
	}
};

class PinnedBar final {
public:
	PinnedBar(
		not_null<QWidget*> parent,
		not_null<Main::Session*> session,
		rpl::producer<PinnedBarId> itemId,
		bool withClose = false);

	void show();
	void hide();
	void raise();

	void move(int x, int y);
	void resizeToWidth(int width);
	[[nodiscard]] int height() const;
	[[nodiscard]] rpl::producer<int> heightValue() const;
	[[nodiscard]] rpl::producer<> closeClicks() const;
	[[nodiscard]] rpl::producer<> barClicks() const;

	[[nodiscard]] rpl::lifetime &lifetime() {
		return _wrap.lifetime();
	}

private:
	void createControls();

	Ui::SlideWrap<> _wrap;
	std::unique_ptr<Ui::MessageBar> _bar;
	std::unique_ptr<Ui::IconButton> _close;
	std::unique_ptr<Ui::PlainShadow> _shadow;
	rpl::event_stream<Ui::MessageBarContent> _content;
	rpl::event_stream<> _barClicks;
	bool _shouldBeShown = false;
	bool _forceHidden = false;

};

} // namespace HistoryView
