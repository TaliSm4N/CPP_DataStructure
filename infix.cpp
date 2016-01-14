#include <iostream>
#include <cstdio>

class Stack
{
		private:
				int top;
				char *ary;
				int capacity;
				void changeSize();

		public:
			Stack();
			bool isEmpty();
			char peek();
			void push(char item);
			void pop();
};

void Stack::changeSize()
{
		char *temp=new char[capacity*2];

		for(int i=0;i<capacity;i++)
				temp[i]=ary[i];

		delete ary;

		ary=temp;

		capacity*=2;
}

Stack::Stack()
{
		capacity=10;

		ary=new char[capacity];

		top=-1;
}

bool Stack::isEmpty()
{
		return top==-1;
}

char Stack::peek()
{
		if(isEmpty())
				return '\0';

		return ary[top];
}

void Stack::push(char item)
{
		if(top==capacity-1)
				changeSize();

		ary[++top]=item;
}

void Stack::pop()
{
		if(isEmpty())
				std::cout<<"Stack is empty"<<std::endl;

		ary[top--]='\0';
}

class Queue
{
		private:
				int front;
				int rear;
				char *ary;
				int capacity;
				void changeSize();

		public:
				Queue();
				void dequeue();
				void enqueue(char item);
				bool isEmpty();
				char peek();
};

Queue::Queue()
{
		capacity=10;

		ary=new char[capacity+1];

		front=0;
		rear=0;
}

void Queue::changeSize()
{
		char *temp=new char[capacity*2+1];

		for(int i=0;;i++)
		{
				temp[i]=ary[(front+i)%(capacity+1)];
		}

		front=0;
}

void Queue::enqueue(char item)
{
		if((rear+1)%(capacity+1)==front)
				changeSize();

		rear++;

		ary[rear%(capacity+1)]=item;
}

void Queue::dequeue()
{
		if(isEmpty())
				return;

		ary[front%(capacity+1)]='\0';

		front++;
}

bool Queue::isEmpty()
{
		return rear==front;
}

char Queue::peek()
{
		if(isEmpty())
				return '\0';

		std::cout<<ary[front+1]<<std::endl;
}

void postfix(char *infix)
{
		int i=0;

		bool check=false;

		Stack op;


		while(!(infix[i]=='\0'))
		{

				if(infix[i]>='0'&&infix[i]<='9')
				{
						std::cout<<infix[i];
				}
				else if(infix[i]=='+'||infix[i]=='-')
				{
						std::cout<<' ';

						while(!op.isEmpty())
						{
								if(op.peek()=='(')
										break;

								std::cout<<op.peek()<<' ';
								op.pop();
						}


						op.push(infix[i]);

						check=false;
				}
				else if(infix[i]=='*'||infix[i]=='/')
				{
						std::cout<<' ';

						if(check)
						{
								while(!op.isEmpty())
								{
										if(op.peek()=='(')
												break;

										std::cout<<op.peek()<<' ';
										op.pop();

									if(op.peek()=='*'||op.peek()=='/')
												break;
								}
						}

						op.push(infix[i]);

						check=true;
				}
				else if(infix[i]=='(')
				{
						op.push(infix[i]);
						//check=false;
				}
				else if(infix[i]==')')
				{
						while(op.peek()!='(')
						{
								std::cout<<' '<<op.peek();
								op.pop();
						}
						op.pop();
				}

				i++;
		}

		while(!op.isEmpty())
		{
				std::cout<<' '<<op.peek();
				op.pop();
		}
}

int main()
{
		char *infix=new char[200];

		scanf("%s",infix);

		postfix(infix);
}
