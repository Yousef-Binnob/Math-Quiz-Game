#include <iostream>
#include<cstdlib>
using namespace std;

enum enQuestionLevel {Easy = 1, Med = 2, Hard = 3, Mix = 4};
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, mix = 5 };
struct stQuestion
{
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	int Number1 = 0, Number2 = 0, CorrectAnswer = 0, PlayerAnswer = 0;
	bool AnswerResult = false;
};
struct stQuizz
{
	stQuestion QuestionList[100];
	unsigned short NumberOfQuestions = 0, NumberOfRightAnswers = 0, NumberOfWrongAnswers = 0;
	enQuestionLevel QuestionsLevel;
	enOperationType OpType;
	bool isPass = false;
};

int ReadIntgerNumberInRange(int from, int to, string message)
{
	int number;

	cout << message;
	cin >> number;

	while (number < from || number > to)
	{
		cout << "Wrong number! Number must be between " << from << " and " << to << endl;
		cout << message;
		cin >> number;
	}
	return number;
}
int RandomNumber(int from, int to)
{
	//Function to generate a random number
	int RandNum = rand() % (to - from + 1) + from;
	return RandNum;
}
void SetScreenColor(bool result)
{
	if (result)
		system("color 2F");
	else
	{
		cout << "\a";
		system("color 4F");
	}
}
void CorrectTheQuestionAnswer(stQuizz& quizz,short QuestionNumber)
{
	if (quizz.QuestionList[QuestionNumber].CorrectAnswer != quizz.QuestionList[QuestionNumber].PlayerAnswer)
	{
		quizz.QuestionList[QuestionNumber].AnswerResult = false;
		quizz.NumberOfWrongAnswers++;
		cout << "Wrong answer :-(\n";
		cout << "The right answer is ";
		cout << quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
		cout << "\n";
	}
	else
	{
		quizz.QuestionList[QuestionNumber].AnswerResult = true;
		quizz.NumberOfRightAnswers++;
		cout << "Right answer :-)\n";
	}
	SetScreenColor(quizz.QuestionList[QuestionNumber].AnswerResult);
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
char GetOperationSymbol(enOperationType OpType)
{
	char OpSymbolsList[4] = { '+','-','*','/' };
	return OpSymbolsList[OpType - 1];
}
string GetOperationName(enOperationType OpType)
{
	string OpNamesList[5] = { "Add" , "Sub" , "Mul" , "Div" , "Mix" };
	return OpNamesList[OpType - 1];
}
string GetLevelName(enQuestionLevel level)
{
	string levels[4] = { "Easy", "Med", "Hard", "Mix" };
	return levels[level - 1];
}
void PrintQuestion(stQuestion question, short QuestionNumber, short NumberOfQuestions)
{
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << NumberOfQuestions << "]\n\n"; 
	cout << question.Number1 << endl;
	cout << question.Number2 << " " << GetOperationSymbol(question.OperationType) << endl;
	cout << "__________" << endl;
}
string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return"PASS :-)";
	else
		return"Fail :-(";
}
void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n_________________________________\n";
	cout << "Final Result is " << GetFinalResultsText(Quizz.isPass) << endl;
	cout << "_________________________________\n";

	cout << "Number of questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Questions level     : " << GetLevelName(Quizz.QuestionsLevel) << endl;
	cout << "OpType              : " << GetOperationName(Quizz.OpType) << endl;
	cout << "Number of right answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of wrong answers: " << Quizz.NumberOfWrongAnswers << endl;
}
int SimpleCalculator(int num1, int num2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return num1 + num2;
	case enOperationType::Sub:
		return num1 - num2;
	case enOperationType::Mul:
		return num1 * num2;
	case enOperationType::Div:
		return num1 / num2;
	default:
		return num1 + num2;
	}
}
stQuestion GenerateQuestion(enQuestionLevel questionLevel, enOperationType OpType)
{
	stQuestion question;
	if (questionLevel == enQuestionLevel::Mix)
		questionLevel = (enQuestionLevel)RandomNumber(1, 3);
	if (OpType == enOperationType::mix)
		OpType = (enOperationType)RandomNumber(1, 4);
	question.OperationType = OpType;

	switch (questionLevel)
	{
	case enQuestionLevel::Easy:
		question.Number1 = RandomNumber(1, 10);
		question.Number2 = RandomNumber(1, 10);

		question.CorrectAnswer = SimpleCalculator(question.Number1, question.Number2, question.OperationType);
		question.QuestionLevel = questionLevel;

		return question;
	case enQuestionLevel::Med:
		question.Number1 = RandomNumber(10, 50);
		question.Number2 = RandomNumber(10, 50);

		question.CorrectAnswer = SimpleCalculator(question.Number1, question.Number2, question.OperationType);
		question.QuestionLevel = questionLevel;

		return question;
	case enQuestionLevel::Hard:
		question.Number1 = RandomNumber(50, 100);
		question.Number2 = RandomNumber(50, 100);

		question.CorrectAnswer = SimpleCalculator(question.Number1, question.Number2, question.OperationType);
		question.QuestionLevel = questionLevel;

		return question;
	}
	return question;
}
void GenerateQuizzQuetions(stQuizz& quizz)
{
	for (short question = 0; question < quizz.NumberOfQuestions; question++)
		quizz.QuestionList[question] = GenerateQuestion(quizz.QuestionsLevel, quizz.OpType);
}
void AskAndCorrectQuestionListAnswers(stQuizz& quizz)
{
	for (short question = 0; question < quizz.NumberOfQuestions; question++)
	{
		PrintQuestion(quizz.QuestionList[question], question, quizz.NumberOfQuestions);
		quizz.QuestionList[question].PlayerAnswer = ReadIntgerNumberInRange(-100000, 100000, "");
		CorrectTheQuestionAnswer(quizz, question);
	}
	quizz.isPass = quizz.NumberOfRightAnswers >= quizz.NumberOfWrongAnswers;
}
void PlayGame()
{
	stQuizz quizz;
	quizz.NumberOfQuestions = ReadIntgerNumberInRange(1, 10, "How many questions do you want to answer ? ");
	quizz.QuestionsLevel = (enQuestionLevel)ReadIntgerNumberInRange(1, 4, "Enter questios level [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ? ");
	quizz.OpType = (enOperationType)ReadIntgerNumberInRange(1, 5, "Enter operation type [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix ? ");

	GenerateQuizzQuetions(quizz);
	AskAndCorrectQuestionListAnswers(quizz);
	PrintQuizzResults(quizz);
}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PlayGame();

		cout << "\n\nDo you want to play again (Y/N) ? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'y'|| PlayAgain == 'Y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}