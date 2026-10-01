#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
using namespace std;

enum enQuestionLevel
{
	Easy = 1,
	Medium = 2,
	Hard = 3,
	Mix = 4
};

enum enOperationType
{
	Addition = 1,
	Subtraction = 2,
	Multiplication = 3,
	Division = 4,
	MixOperation = 5
};

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuiz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool isPassed = false;
};

short readNumberOfQuestions()
{
	short numberOfQuestions=1;
	do
	{
		cout << "How Many Questions Do You Want To Answer ? ";
		cin >> numberOfQuestions;
	} while (numberOfQuestions < 1 || numberOfQuestions > 10);
	return numberOfQuestions;
}

enQuestionLevel readQuestionLevel()
{
	short QuestionLevel = 0;
	do
	{
		cout << "Enter Questions Level [1] Easy , [2] Medium , [3] Hard , [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);
	return (enQuestionLevel)QuestionLevel;
}

enOperationType readOperationType()
{
	short OperationType;
	do
	{
		cout << "Enter Operation Type [1] Addition , [2] Subtraction , [3] Multiplication , [4] Division , [5] Mix ? ";
		cin >> OperationType;
	} while (OperationType < 1 || OperationType > 5);
	return (enOperationType)OperationType;
}

int randomNumber(int From, int To)
 {
	 return rand() % (To - From + 1) + From;
 }

enOperationType getRandomOperationType()
{
	 int op = randomNumber(1, 4);
	 return (enOperationType)op;
}

int simpleCalculator(int Number1, int Number2, enOperationType OperationType)
{
	 switch (OperationType)
	 {	
	 case Addition:
		 return Number1 + Number2;
		 break;
	 case Subtraction:
		 return Number1 - Number2;
		 break;
	 case Multiplication:
		 return Number1 * Number2;
		 break;
	 case Division:
		 return Number1 / Number2;
		 break;
	 default:
		 return Number1 + Number2;
		 break;
	 }
}

stQuestion generateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
	stQuestion Question;
	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)randomNumber(1, 3);
	}
	if (OperationType == enOperationType::MixOperation)
	{
		OperationType = getRandomOperationType();
	}
	Question.OperationType = OperationType;

	switch (QuestionLevel)
	{
	case Easy:
		Question.Number1 = randomNumber(1, 10);
		Question.Number2 = randomNumber(1, 10);
		if (Question.OperationType == enOperationType::Division)
		Question.Number1 = Question.Number2 * randomNumber(1, 10);

		Question.CorrectAnswer = simpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case Medium:
		Question.Number1 = randomNumber(10, 50);
		Question.Number2 = randomNumber(10, 50);
		if (Question.OperationType == enOperationType::Division)
		Question.Number1 = Question.Number2 * randomNumber(1, 10);

		Question.CorrectAnswer = simpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case Hard:
		Question.Number1 = randomNumber(50, 100);
		Question.Number2 = randomNumber(50, 100);
		if (Question.OperationType == enOperationType::Division)
		Question.Number1 = Question.Number2 * randomNumber(1, 10);

		Question.CorrectAnswer = simpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	default:
		Question.Number1 = randomNumber(1, 100);
		Question.Number2 = randomNumber(1, 100);
		if (Question.OperationType == enOperationType::Division)
		Question.Number1 = Question.Number2 * randomNumber(1, 10);

		Question.CorrectAnswer = simpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}

}

void generateQuizQuestions(stQuiz& Quiz)
{
	for (short QuestionIndex = 0; QuestionIndex < Quiz.NumberOfQuestions; QuestionIndex++)
	{
		Quiz.QuestionList[QuestionIndex] = generateQuestion(Quiz.QuestionLevel, Quiz.OperationType);
	}
}

string getOpTypeSympol(enOperationType OperationType)
{
	switch (OperationType)
	{
	case Addition:
		return "+" ;
		break;
	case Subtraction:
		return "-";
		break;
	case Multiplication:
		return "*";
		break;
	case Division:
		return "/";
		break;
	default:
		return "Mix";
		break;
	}
}
 
void printTheQuestion(stQuiz& Quiz,short QuestionIndex)
{
	cout << "\nQuestion [" << QuestionIndex + 1 << "/" << Quiz.NumberOfQuestions << "] : \n\n";
	cout << Quiz.QuestionList[QuestionIndex].Number1 << "\n";
	cout << Quiz.QuestionList[QuestionIndex].Number2 << " ";
	cout << getOpTypeSympol(Quiz.QuestionList[QuestionIndex].OperationType) << "\n_____________\n";
}
 
int readQuestionAnswer()
{
	int UserAnswer = 0;
	cin >> UserAnswer;
	return UserAnswer;
}

void setScreenColor(bool Right)
 {
	 if(Right)
		 system("Color 2F");
	 else
	 {
		 cout << "\a";
		 system("Color 4F");
	 }
 }
 
void correctTheQuestionAnswer(stQuiz& Quiz, short QuestionIndex)
{
	if(Quiz.QuestionList[QuestionIndex].PlayerAnswer != Quiz.QuestionList[QuestionIndex].CorrectAnswer)
	{
		Quiz.QuestionList[QuestionIndex].AnswerResult = false;
		Quiz.NumberOfWrongAnswers++;

		cout << "Wrong Answer, :-(\n";
		cout << "The Right Answer is: " << Quiz.QuestionList[QuestionIndex].CorrectAnswer << endl;
 
	}
	else
	{
		Quiz.QuestionList[QuestionIndex].AnswerResult = true;
		Quiz.NumberOfRightAnswers++;

		cout << "Right Answer :-)\n";
		 
	}
	cout << endl;
	setScreenColor(Quiz.QuestionList[QuestionIndex].AnswerResult);
}

void askAndCorrectQuestionListAnswers(stQuiz& Quiz)
{
	for (short QuestionIndex = 0; QuestionIndex < Quiz.NumberOfQuestions; QuestionIndex++)
	{
		printTheQuestion(Quiz,QuestionIndex);

		Quiz.QuestionList[QuestionIndex].PlayerAnswer = readQuestionAnswer();

		correctTheQuestionAnswer(Quiz, QuestionIndex);
	}
	Quiz.isPassed = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}

string getQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string arrQuestionLevel[] = { "Easy", "Medium", "Hard", "Mix" };
	return arrQuestionLevel[QuestionLevel - 1];
}

string getFinalResultText(bool isPassed)
{
	return (isPassed) ? "Passed :-)" : "Failed :-(";
}

void printQuizResults(stQuiz& Quiz)
{
	cout << "\n_____________________________________\n\nFinal Results is ";
	cout << getFinalResultText(Quiz.isPassed) ;
	cout << "\n_____________________________________\n\n";

	cout << "Number Of Questions     : " << Quiz.NumberOfQuestions << endl;
	cout << "Question Level          : " << getQuestionLevelText(Quiz.QuestionLevel) << endl;
	cout << "OperationType           : " << getOpTypeSympol(Quiz.OperationType) << endl;
	cout << "Number Of Right Answers : " << Quiz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers : " << Quiz.NumberOfWrongAnswers << endl;
	cout << "_____________________________________\n";
}

void playMathGame()
{
	stQuiz Quiz;
	Quiz.NumberOfQuestions = readNumberOfQuestions();
	Quiz.QuestionLevel = readQuestionLevel();
	Quiz.OperationType = readOperationType();

	generateQuizQuestions(Quiz);
	askAndCorrectQuestionListAnswers(Quiz);

	printQuizResults(Quiz);
}

void resetScreen()
{
	system("cls");
	system("color 0F");
}

void startGame()
{
	char PlayAgain = 'Y';
	do
	{
		resetScreen();
		playMathGame();

		cout << "\nDo You Want To Play Again ? [Y/N] ";
		cin >> PlayAgain;

	} while (toupper(PlayAgain) == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));
	startGame();
	return 0;
}