import django.http
import json
import traceback

#all modules should be imported here

from django.shortcuts import render
from django.template import RequestContext
from django.http import HttpResponse
from django.shortcuts import redirect

import lzwpy.views

    
def index(request):
    # return render_to_response('entry.html', {}, context_instance=RequestContext(request))
    return render(request, 'index.html')
    

def ajax(request, module, function):
    """dispatch ajax requests"""
    try:
        fun = getattr(getattr(globals()[str(module)], 'views'), str(function))
        data = json.dumps( fun(request.GET) )
        return django.http.HttpResponse(data, content_type='application/json')
    except:
        # return render_to_response('game.html', {}, context_instance=RequestContext(request))
        return render(request, 'index.html')
