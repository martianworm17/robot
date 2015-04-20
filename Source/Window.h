////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------- //
//                                                                            //
//                       (C) 2010-2015 Robot Developers                       //
//                       See LICENSE for licensing info                       //
//                                                                            //
// -------------------------------------------------------------------------- //
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------//
// Prefaces                                                                   //
//----------------------------------------------------------------------------//

#ifndef ROBOT_WINDOW_H
#define ROBOT_WINDOW_H

#include "Types.h"
#include <string>
#include <vector>

#ifdef ROBOT_OS_MAC
	#include <memory>
#endif

namespace Robot {
	class Process;
	class Window;



//----------------------------------------------------------------------------//
// Types                                                                      //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////

typedef std::vector<Window> WindowList;



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////

class ROBOT_EXPORT Window
{
	friend class Process;

public:
	explicit			Window			(uintptr handle = 0);

public:
	bool				IsValid			(void) const;
	void				Close			(void);

	bool				IsTopMost		(void) const;
	bool				IsBorderless	(void) const;
	bool				IsMinimized		(void) const;
	bool				IsMaximized		(void) const;

	void				SetTopMost		(bool state);
	void				SetBorderless	(bool state);
	void				SetMinimized	(bool state);
	void				SetMaximized	(bool state);

	Process				GetProcess		(void) const;
	int32				GetPID			(void) const;

	uintptr				GetHandle		(void) const;
	bool				SetHandle		(uintptr handle);
	uintptr				GetHandleAx		(void) const;

	std::string			GetTitle		(void) const;
	void				SetTitle		(const char* title);

	Bounds				GetBounds		(void) const;
	void				SetBounds		(const Bounds&  b);
	void				SetBounds		(int32 x, int32 y,
										 int32 w, int32 h);

	Bounds				GetClient		(void) const;
	void				SetClient		(const Bounds&  b);
	void				SetClient		(int32 x, int32 y,
										 int32 w, int32 h);

	Point				MapToClient		(const  Point&  point) const;
	Point				MapToScreen		(const  Point&  point) const;
	Bounds				MapToClient		(const Bounds& bounds) const;
	Bounds				MapToScreen		(const Bounds& bounds) const;

	static WindowList	GetList			(const char* title = nullptr);

	static Window		GetActive		(void);
	static void			SetActive		(const Window& window);

	static bool			IsAxEnabled		(bool options = false);

private:
	static WindowList	GetList			(const char* title, int32 pid);

public:
	bool				operator ==		(const Window& window) const;
	bool				operator !=		(const Window& window) const;

	bool				operator ==		(uintptr handle) const;
	bool				operator !=		(uintptr handle) const;

private:
#ifdef ROBOT_OS_LINUX

	uintptr mHandle;					// Handle to an X11 window

#endif
#ifdef ROBOT_OS_MAC

	std::shared_ptr
		<std::pair<uintptr,				// Handle to a CGWindowID
		 uintptr>> mHandle;				// Handle to a AXUIElementRef

#endif
#ifdef ROBOT_OS_WIN

	uintptr mHandle;					// Handle to a window HWND

#endif
};

}
#endif // ROBOT_WINDOW_H
