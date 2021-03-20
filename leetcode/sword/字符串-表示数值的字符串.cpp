//page 127
class Solution
{
public:
    // bool isNumeric(char *string)
    // {
    //     if (string == nullptr)
    //         return false;

    //     if (*string == '+' || *string == '-')
    //         string++;
    //     while (*string != '\0' && *string <= '9' && *string >= '0')
    //         string++;
    //     if (*string == '\0')
    //         return true;
    //     else if (*string == '.' || *string == 'E' || *string == 'e')
    //         ;
    //     else
    //         return false;

    //     if (*string == '.')
    //     {
    //         string++;
    //         while (*string != '\0' && *string <= '9' && *string >= '0')
    //             string++;
    //         if (*string == '\0')
    //             return true;
    //         else if (*string == 'E' || *string == 'e')
    //             ;
    //         else
    //             return false;
    //     }

    //     if (*string == 'E' || *string == 'e')
    //     {
    //         string++;
    //         if (*string == '\0')
    //             return false;
    //         if (*string == '+' || *string == '-')
    //             string++;
    //         while (*string != '\0' && *string <= '9' && *string >= '0')
    //             string++;
    //         if (*string == '\0')
    //             return true;
    //         else
    //             return false;
    //     }
    // }
    // bool isNumeric(char *string)
    // {
    //     if (*string == '+' || *string == '-')
    //         string++;

    //     //is_number
    //     bool flag_1 = false;
    //     while (*string >= '0' && *string <= '9')
    //     {
    //         string++;
    //         flag_1 = true;
    //     }

    //     if (*string == '.')
    //     {
    //         string++;
    //         bool flag_2 = false;
    //         while (*string >= '0' && *string <= '9')
    //         {
    //             string++;
    //             flag_2 = true;
    //         }
    //         if ((*string == 'e' || *string == 'E') && flag_2 == true)
    //         {

    //             string++;
    //             if (*string == '+' || *string == '-')
    //                 string++;
    //             bool flag_3 = false;
    //             while (*string >= '0' && *string <= '9')
    //             {
    //                 string++;
    //                 flag_3 = true;
    //             }
    //             if (*string == '\0')
    //                 return flag_3;
    //             else
    //                 return false;
    //         }
    //         else if (*string=='\0')
    //         {
    //             return flag_2;
    //         }
    //         else
    //             return false;
    //     }
    //     else if ((*string == 'e' || *string == 'E') && flag_1 == true)
    //     {
    //         string++;
    //         if (*string == '+' || *string == '-')
    //             string++;

    //         bool flag_3 = false;
    //         while (*string >= '0' && *string <= '9')
    //         {
    //             string++;
    //             flag_3 = true;
    //         }
    //         if (*string == '\0')
    //             return flag_3;
    //         else
    //             return false;
    //     }
    //     else if (*string=='\0')
    //     {
    //         return true;
    //     }

    //     else
    //         return false;
    // }

    bool isInter(char *&string)
    {
        char * temp=string;
        while (*string >= '0' && *string <= '9')
        {
            string++;
        }
        return temp!=string;
    }

    bool isNumeric(char *string)
    {
        if (string == nullptr)
            return false;

        if (*string == '+' || *string == '-')
            string++;
        bool flag_inter1 = isInter(string);
        
        if(*string == '.')
        {
            string++;            
            //小数点两边必须至少存在一个
            flag_inter1 = isInter(string)||flag_inter1;
        }     

        if (*string=='e'||*string=='E')
        {
            string++;
            if (*string == '+' || *string == '-')
                string++;
            //出现e之后必须保证e的两边都存在
            flag_inter1 = isInter(string)&&flag_inter1;
        }
        //必须最后一个是'\0'
        return *string=='\0'&&flag_inter1;
        
    }
};

int main()
{
    char string[] = "+.12";
    Solution solution;
    bool result = solution.isNumeric(string);
    return 0;
}
