#pragma once

#include <iostream>
#include <string>

/*MVP架构
* Model（模型）：管理数据和业务逻辑
* View（视图）：负责显示数据，定义 UI 接口，不直接操作 Model
* Presenter（展示者/协调器））：负责处理逻辑，控制 Model 与 View 交互（View 不直接访问 Model）
* 与MVC区别：
* 在 MVP 中，View 被动
* 所有逻辑都放到 Presenter
* 更加便于 单元测试 Presenter
* 
* 彻底解耦
* 可测试性强
* View 只负责展示和响应用户操作
* 可轻松更换 View
* 
* Model:管理数据、业务逻辑
* View:显示数据、接收用户交互（通过接口调用 Presenter）
* Presenter:处理业务逻辑，调用 Model 并更新 View
*/

class UserModel
{
public:
	bool ValiddateUser(const std::string& username, const std::string& password)
	{
		return username == "admin" && password == "1234";
	}
};


class ILoginView
{
public:
	virtual ~ILoginView() = default;
	virtual void ShowMessage(const std::string& msg) = 0;
	virtual void ClearInput() = 0;
};

class LoginPresenter
{
public:
	LoginPresenter(ILoginView& v, UserModel& m) : view(v), model(m) {}

	void OnLoginClicked(const std::string& username, const std::string& password)
	{
		if (model.ValiddateUser(username, password))
		{
			view.ShowMessage("Login successful !");
		}
		else
		{
			view.ShowMessage("Invalid username or password");
			view.ClearInput();
		}
	}

private:
	ILoginView& view;
	UserModel& model;
};

class ConsoleLoginView : public ILoginView
{
public:
	ConsoleLoginView(LoginPresenter* p) : presenter(p) {}

	void Show()
	{
		std::string username, password;
		std::cout << "Username: ";
		std::cin >> username;
		std::cout << "Password: ";
		std::cin >> password;
		presenter->OnLoginClicked(username, password);
	}

	void ShowMessage(const std::string& msg) override
	{
		std::cout << "[View] " << msg << std::endl;
	}

	void ClearInput() override
	{
		std::cout << "[View] Please re-enter your login info." << std::endl;
	}

private:
	LoginPresenter* presenter;
};