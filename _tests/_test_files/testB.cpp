#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
using namespace std;

//------------------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/_SFML/animate.h"
//------------------------------------------------------------------------------------------

bool test_stub(bool debug=false){
  return true;
}
bool test_token(bool debug=false){
  Token* tptr;
  tptr=new Integer(5);
  cout<<*tptr<<endl;
  delete tptr;
  Variable var1("x");
  cout<<var1<<endl;
  tptr=&var1;
  cout<<*tptr<<endl;
  return true;
}
bool test_RPN(bool debug = false){
  cout<<"test"<<endl;
  Queue<Token *> postfix;
  postfix.push(new Integer(3));
  postfix.push(new Integer(5));
  postfix.push(new Operator("*"));
  cout<<postfix;
  RPN rpn(postfix);

  // Queue<Token*> copyCtor=postfix;
  // cout<<"copyqueue: "<<copyCtor;
  // cout<<"postfix var: "<<rpn._postfix;
  
  cout << "3 5 *: " << rpn() << endl;
  if(rpn()!=15)
    return false;
  cout << "-------------" << endl;
  Queue<Token *> postfix2;
  postfix2.push(new Integer(3));
  postfix2.push(new Variable("X"));
  postfix2.push(new Operator("*"));
  rpn.set_input(postfix2);
  cout << "3 x *: (x=2): " << rpn(2) << endl;
  if(rpn(2)!=6)
    return false;
  return true;
}
bool test_SY(bool debug=false){
  Queue<Token*> infix;
  infix.push(new Integer(3));
  infix.push(new Operator("*"));
  infix.push(new Integer(5));

  cout<<"infix queue: "<<infix<<endl;

  ShuntingYard sy(infix);
  Queue<Token*> postfix = sy.postfix();
  RPN rpn(postfix);
  cout << "3 * 5: " << rpn() << endl;
  if(rpn()!=15)
    return false;

  Queue<Token *> infix2;
  infix2.push(new Integer(3));
  infix2.push(new Operator("*"));
  infix2.push(new LeftParen());
  infix2.push(new Integer(5));
  infix2.push(new Operator("+"));
  infix2.push(new Integer(6));
  infix2.push(new Operator("-"));
  infix2.push(new Variable("X"));
  infix2.push(new RightParen());
  infix2.push(new Operator("/"));
  infix2.push(new Integer(9));
  
  cout<<"infix queue: "<<infix2<<endl;
  
  sy.infix(infix2);
  postfix = sy.postfix();
  rpn.set_input(postfix);
  cout << "3*(5+6-X)/9 (x=2): " << rpn(2) << endl;
  if(rpn(2)!=3)
    return false;

  //
  
  ShuntingYard sy2;
  postfix = sy2.postfix(infix2);
  for (Queue<Token *>::Iterator it = postfix.begin(); it != postfix.end(); it++){
    cout <<setw(3)<< *it;
  }
  cout << endl;

  //

  Queue<Token *> infix3;
  infix3.push(new Integer(3));
  infix3.push(new Operator("+"));
  infix3.push(new Integer(4));
  infix3.push(new Operator("*"));
  infix3.push(new Integer(2));
  infix3.push(new Operator("/"));
  infix3.push(new LeftParen());
  infix3.push(new Integer(1));
  infix3.push(new Operator("-"));
  infix3.push(new Integer(5));
  infix3.push(new RightParen());
  infix3.push(new Operator("^"));
  infix3.push(new Integer(2));
  infix3.push(new Operator("^"));
  infix3.push(new Integer(3));
  
  cout<<"infix queue: "<<infix3<<endl;
  cout <<"infix expected: 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3" << endl;
  
  sy.infix(infix3);
  postfix = sy.postfix();
  cout <<"postfix expected: 3 4 2 * 1 5 - 2 3 ^ ^ / +" << endl;
  cout <<"postfix queue: "<<postfix<<endl;

  rpn.set_input(postfix);
  cout<<"result: "<<rpn()<<endl;

  return true;
}
bool test_TOKENS(bool debug=false){
  Token* t1=new Operator("+");
  cout<<"type for "<<t1<<": "<<t1->Type()<<endl;
  if(t1->Type()!=OPERATOR)
    return false;
  Token* t2=new Variable("y");
  cout<<"type for "<<t1<<": "<<t2->Type()<<endl;
  if(t2->Type()!=VARIABLE)
    return false;
  Token* t3=new Function("sin");
  cout<<"type for "<<t1<<": "<<t3->Type()<<endl;
  if(t3->Type()!=FUNCTION)
    return false;
  return true;
}
bool test_TK_STR(bool debug=false){
  Tokenize str1("1 + 3 - 4");
  Queue<Token*> queue1;
  queue1=str1.get_token_queue();
  if(queue1.size()!=5)
    return false;

  Tokenize str2("3 x *");
  Queue<Token*> queue2;
  queue2=str2.get_token_queue();
  cout<<queue2<<endl;
  if(queue2.size()!=3)
    return false;
  
  RPN rpn(queue2);
  cout<<rpn(7)<<endl;
  if(rpn(7)!=21)
    return false;
  
  Tokenize str3("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
  Queue<Token*> queue3;
  queue3=str3.get_token_queue();
  cout<<"infix queue: "<<queue3<<endl;
  cout <<"infix expected: 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3" << endl;
  
  ShuntingYard sy;
  sy.infix(queue3);
  Queue<Token*> postfix = sy.postfix();
  cout <<"postfix expected: 3 4 2 * 1 5 - 2 3 ^ ^ / +" << endl;
  cout <<"postfix queue: "<<postfix<<endl;

  rpn.set_input(postfix);
  cout<<"result: "<<rpn()<<endl;
  cout<<"expect around 3.00012"<<endl;
  if(abs(rpn()-3.00012)>0.01)
    return false;

  cout<<"============================================================="<<endl;

  Tokenize str4("x * cos ( 1 / x )");
  Queue<Token*> queue4;
  queue4=str4.get_token_queue();
  if(queue4.size()!=8)
    return false;

  cout<<"infix queue:     "<<queue4;
  cout <<"infix expected: x * cos ( 1 / x )" << endl;
  
  sy.infix(queue4);
  Queue<Token*> postfix4 = sy.postfix();
  cout <<"postfix expected: x 1 x / cos *" << endl;
  cout <<"postfix queue: "<<postfix4<<endl;
  if(postfix4.size()!=6)
    return false;

  rpn.set_input(postfix4);
  cout<<"result (x=4): "<<rpn(4)<<endl;
  cout<<"expect around 3.876"<<endl;
  if(abs(rpn()-3.87565)>0.01)
    return false;

  return true;
}
bool test_coords(bool debug=false){
  return true;
}
bool test_structs(bool debug=false){
  // GraphInfo v1;
  // cout<<v1<<endl;
  // GraphInfo v2(-5,5);
  // cout<<v2<<endl;
  // GraphInfo v3(5,5,-5,-5);
  // cout<<v3<<endl;
  // cout<<"=============================="<<endl;
  // point p1;
  // cout<<p1<<endl;
  // point p2(-7,3);
  // cout<<p2<<endl;
  // cout<<"=============================="<<endl;
  // cout<<v1<<" GraphInfo of "<<p1<<"?"<<endl;
  // cout<<boolalpha<<v1.in_view(p1)<<endl;
  // if(!v1.in_view(p1))
  //   return false;
  // cout<<v1<<" GraphInfo of "<<p2<<"?"<<endl;
  // cout<<boolalpha<<v1.in_view(p2)<<endl;
  // if(v1.in_view(p2))
  //   return false;
  return true;
}
bool test_plot(bool debug=false){
  GraphInfo* info = new GraphInfo();
  {
    info->_equation="x ^ 2 - 2";
    info->_window_dimensions=sf::Vector2f(GRAPH_WIDTH,GRAPH_HEIGHT);
    info->_origin=sf::Vector2f(GRAPH_WIDTH/2,GRAPH_HEIGHT/2);
    info->_domain=sf::Vector2f(-4,4);
    info->_range=sf::Vector2f(-4,4);
    info->_num_points=4;
    info->_delta=((info->_domain.y-info->_domain.x)/info->_num_points);                     //????????
    info->_scale=sf::Vector2f(GRAPH_WIDTH/info->_num_points,GRAPH_HEIGHT/(info->_range.y-info->_range.x)); //????????
    info->_angle=0;
  }
  Plot p(info);
  vector<sf::Vector2f> coords=p();
  cout<<"points for domain: [-4,4], 4 pts";
  // for(int i=0; i<coords.size(); i++){
  //   cout<<coords.at(i)<<" ";
  // }
  return true;
}
bool test_graph1(bool debug=false){
  GraphInfo* info = new GraphInfo();
  {
    info->_equation="x - 2";
    info->_window_dimensions=sf::Vector2f(GRAPH_WIDTH,GRAPH_HEIGHT);
    info->_origin=sf::Vector2f(GRAPH_WIDTH/2,GRAPH_HEIGHT/2);
    info->_domain=sf::Vector2f(-10,10);
    info->_num_points=10;
    info->_delta=((info->_domain.y-info->_domain.x)/info->_num_points);                     //????????
    info->_scale=sf::Vector2f(GRAPH_WIDTH/info->_num_points,GRAPH_HEIGHT/info->_num_points); //????????
    info->_angle=0;
  }
  cout<<"_info should be address "<<info<<endl;
  Graph g(info);
  cout<<"g instantiated successfully: ";
  g.printpts();
  // g.set_info();
  Plot p(info);

  sf::Vector2f test();
  cout<<test;

  // vector<sf::Vector2f> coords=p();
  // cout<<"points for domain: [-4,4], 4 pts"<<endl;
  // for(int i=0; i<coords.size(); i++){
  //   cout<<coords.at(i)<<" ";
  // }
  return true;
}
bool test_graph2(bool debug=false){
  GraphInfo* info = new GraphInfo();
  info->_equation="x - 2";
  cout<<"info->_eq: "<<info->_equation<<endl;
  Graph g(info);
  cout<<"pts for eq: x-2";
  g.printpts();

  info->_equation="2 * x - 1";
  cout<<"pts for eq: x-2";
  g.update();
  g.printpts();

  return true;
}
bool test_graph_comp(bool debug=false){
  GraphInfo* _info=new GraphInfo();
  _info->_window_dimensions=sf::Vector2f(GRAPH_WIDTH,GRAPH_HEIGHT);
  _info->_origin=sf::Vector2f(GRAPH_WIDTH/2,GRAPH_HEIGHT/2);
  _info->_domain=sf::Vector2f(DOMAIN_MIN,DOMAIN_MAX);
  _info->_range=sf::Vector2f(RANGE_MIN,RANGE_MAX);
  _info->_num_points=NUM_POINTS;
  _info->_delta=((_info->_domain.y-_info->_domain.x)/(_info->_num_points-1));
  _info->_scale=sf::Vector2f(GRAPH_WIDTH/(_info->_num_points-1),GRAPH_HEIGHT/(_info->_num_points-1)); //????????
  _info->_angle=0;                        //????????

  _info->_equation="x";
  Graph g(_info);
  g.printpts();
  
  _info->_equation="x ^ 2";
  g.update();
  g.printpts();

  _info->_equation="( 5 / 4 ^ 3 ) * ( x ^ 3 ) - 1";
  g.update();
  g.printpts(); 

  return true;
}

TEST(TEST_STUB, TestStub) {
  EXPECT_EQ(1, test_stub(false));
}
TEST(TEST_B, TestB) {
  EXPECT_EQ(1, test_graph_comp(false));
}
TEST(TEST_A, TestA) {
  EXPECT_EQ(1, test_token(false));
}
TEST(TEST_COPIES, TestCopies) {
  EXPECT_EQ(1, test_RPN(false));
  cout<<endl<<"=========================="<<endl<<endl;
  EXPECT_EQ(1, test_SY(false));
  cout<<endl<<"=========================="<<endl<<endl;
  EXPECT_EQ(1, test_TOKENS(false));
}
TEST(TEST_OTHER, TestOther) {
  EXPECT_EQ(1, test_TK_STR(false));
}
TEST(TEST_OLD_GRAPH, TestOldGraph) {
  EXPECT_EQ(1, test_coords(false));
  EXPECT_EQ(1, test_structs(false));
}
TEST(TEST_GRAPH, TestGraph) {
  cout<<endl<<"============pl============="<<endl<<endl;
  EXPECT_EQ(1, test_plot(false));
  cout<<endl<<"============g1============="<<endl<<endl;
  EXPECT_EQ(1, test_graph1(false));
  cout<<endl<<"============g2============"<<endl<<endl;
  EXPECT_EQ(1, test_graph2(false));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}