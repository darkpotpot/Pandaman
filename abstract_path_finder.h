#ifndef ABSTRACT_PATH_FINDER_H
#define ABSTRACT_PATH_FINDER_H

#include <list>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

struct CaseInfo{
    //Case * parent;
    const void * parent;
    double dist_from_start;
    double dist_to_end;
};


template<typename Case>
class AbstractPathFinder{
public:
    virtual float dist_between(const Case*const c1, const Case*const c2)=0;
    virtual list<const Case*> get_neighbors(const Case* c)=0;
    //---------
    list<const Case*> find_best_path(const Case *const start, const Case * const  end)
    {
        const Case* current;
        map<const Case*, CaseInfo> case_to_info;
        list<const Case*> open_list;
        list<const Case*> closed_list;
        list<const Case*> neighbors;
        open_list.push_back(start);
        CaseInfo ci = {NULL, 0, dist_between(start, end)};
        case_to_info[start] = ci;
        current = start;
        while ((current!=end) &&(!open_list.empty()))
        {
            
            current = get_best_case(&open_list, case_to_info);
            open_list.remove(current);
            closed_list.push_back(current);
            neighbors = get_neighbors(current);
            list<const Case*>::const_iterator it;
            list<const Case*>::const_iterator find_it;
            for(it=neighbors.begin();it!=neighbors.end();it++)
            {
                find_it = find(closed_list.begin(), closed_list.end(), (*it));
                if (find_it==closed_list.end())
                {
                    update_case(current, (*it), end, case_to_info);
                    open_list.push_back((*it));
                }
            }
        }
        list<const Case*> result;
        if (current==end)
        {
            const Case* case_res = current;
            while (case_res!=NULL)
            {
                result.push_front(case_res);
                case_res = static_cast<const Case*>(case_to_info[case_res].parent);
            }
        }
        return result;
    }

    const Case* get_best_case(list<const Case*> *list_case, map<const Case*, CaseInfo> &case_to_info)
    {
        const Case * current_case = list_case->front();
        CaseInfo current_case_info = case_to_info[current_case];
        double min_dist = current_case_info.dist_from_start+current_case_info.dist_to_end;
        double current_dist = min_dist;
        for (list<const Case*>::iterator it=list_case->begin();it!=list_case->end();it++)
            {
                current_case_info = case_to_info[(*it)];
                current_dist = current_case_info.dist_from_start+current_case_info.dist_to_end;
                if (current_dist<min_dist)
                {
                    min_dist = current_dist;
                    current_case = (*it);
                }
            }        
        return current_case;
    }
    void update_case(const Case* parent_case, const Case* current_case, const Case* end_case, map<const Case*, CaseInfo>& case_to_info)
    {
        double dist_to_current = case_to_info[parent_case].dist_from_start+dist_between(parent_case, current_case);
        map<const Case*, CaseInfo>::iterator it;
        it = case_to_info.find(current_case);
        if (it==case_to_info.end())
        {
            CaseInfo ci = {parent_case, dist_to_current, dist_between(current_case, end_case)};
            case_to_info[current_case] = ci;
        }
        else if (dist_to_current<it->second.dist_from_start)
        {
            CaseInfo ci = {parent_case, dist_to_current, dist_between(current_case, end_case)};
            case_to_info[current_case] = ci;
        }
    }

};


#endif