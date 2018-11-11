/*******************************************************************************
 * gui/common/RSTextBrowser.h                                                  *
 *                                                                             *
 * Copyright (C) 2018 RetroShare Team <retroshare.team@gmail.com>              *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU Affero General Public License as              *
 * published by the Free Software Foundation, either version 3 of the          *
 * License, or (at your option) any later version.                             *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU Affero General Public License for more details.                         *
 *                                                                             *
 * You should have received a copy of the GNU Affero General Public License    *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.       *
 *                                                                             *
 *******************************************************************************/

#ifndef RSTEXTBROWSER_H
#define RSTEXTBROWSER_H

#include <QTextBrowser>
#include "util/RsSyntaxHighlighter.h"

//#define RSTEXTBROWSER_CHECKIMAGE_DEBUG 1

class RSImageBlockWidget;

//cppcheck-suppress noConstructor
class RSTextBrowser : public QTextBrowser
{
	Q_OBJECT

	Q_PROPERTY(QColor textColorQuote READ textColorQuote WRITE setTextColorQuote)

public:
	explicit RSTextBrowser(QWidget *parent = 0);

	void setPlaceholderText(const QString &text);
	void setImageBlockWidget(RSImageBlockWidget *widget);
	void resetImagesStatus(bool load);
	QPixmap getBlockedImage();
	bool checkImage(QPoint pos, QString &imageStr);
	bool checkImage(QPoint pos) {QString imageStr; return checkImage(pos, imageStr); }
	QString anchorForPosition(const QPoint &pos) const;


	void activateLinkClick(bool active);

	virtual QVariant loadResource(int type, const QUrl &name);

	QColor textColorQuote() const { return highlighter->textColorQuote();}
	bool getShowImages() const { return mShowImages; }

public slots:
	void showImages();
	void setTextColorQuote(QColor textColorQuote) { highlighter->setTextColorQuote(textColorQuote);}

private slots:
	void linkClicked(const QUrl &url);
	void destroyImageBlockWidget();

protected:
	void paintEvent(QPaintEvent *event);

private:
	QString mPlaceholderText;
	bool mShowImages;
	RSImageBlockWidget *mImageBlockWidget;
	bool mLinkClickActive;
	RsSyntaxHighlighter *highlighter;
#ifdef RSTEXTBROWSER_CHECKIMAGE_DEBUG
	QRect mCursorRectStart;
	QRect mCursorRectLeft;
	QRect mCursorRectRight;
	QRect mCursorRectEnd;
#endif
};

#endif // RSTEXTBROWSER_H
