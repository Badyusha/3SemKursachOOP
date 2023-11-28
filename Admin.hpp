#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "Employee.hpp"

namespace admin {

	class Admin : public employee::Employee {

	public:
		Admin() : Employee() {};
		Admin(const int& id_, const std::string& name_, const std::string& password_);
		Admin(const Admin& admin);
		~Admin() {};

		void showPersonalInfo() const override {};
		void changePersonalInfo() override {};

		int writeIntoFile();

		friend std::ostream& operator <<(std::ostream& s, const Admin* admin);
		friend inline std::istream& operator >>(std::istream& in, Admin& admin);
	};

	inline Admin::Admin(const Admin& admin) { 	}

	inline Admin::Admin(const int& id_, const std::string& name_, const std::string& password_)
				: Employee(id_, name_, password_) {}



	inline int Admin::writeIntoFile() {
		std::ofstream output("Admin.txt", std::ios::out | std::ios::app);

		if (!output.is_open()) {
			std::cout << "Невозможно открыть файл для записи данных!\n"
				"Все данные будут утеряны!\n"
				"Хотите остаться? (д): ";
			std::string choice;
			getline(std::cin, choice);

			for (auto letter : choice) { tolower(letter); }

			if (choice == "д" || choice == "да") {
				system("cls");
				return EXIT;
			}
		}

		output << this;
		output.close();

		return STABLE;
	}



	inline std::ostream& operator <<(std::ostream& s, const Admin* admin) {
		s << admin->getId() << '\t' << admin->getPassword()
			<< "\t" << admin->getName() << "\n";
		return s;
	}

	inline std::istream& operator >>(std::istream& in, Admin& admin) {
		int id = 0, personalNumber = 0;
		std::string password, name;

		in >> id;
		if (!id) { return in; }

		in >> personalNumber >> password;
		getline(in, name);
		name.erase(name.begin(), name.begin() + STATE::STABLE);

		admin.setId(id);
		admin.setName(name);
		admin.setPassword(password);

		return in;
	}



	inline int registerAdmin(std::vector<Person*>& usersVector) {
		auto adminInfoPair = reg();

		int id = usersVector.size() + ID_NUM::MIN_ID_NUM;
		for (auto user : usersVector) {
			if (user->getId() != id) {
				break;
			}
			id++;
		}

		std::cout << "\nВаш ID для авторизации: " << id << "\nНайти его можно также в вашем личном кабинете\n" << std::endl;

		try {
			//usersVector.push_back(new Admin(id, "name", encrypt("password"), 0));
		}
		catch (std::bad_alloc) {
			std::cout << "Недостаточно памяти!\nЗапись приостановлена";
		}

		std::cout << std::endl;
		system("pause");
		system("cls");

		return id;
	}
}

#endif